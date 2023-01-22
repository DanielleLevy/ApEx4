//
// Created by danie on 11/01/2023.
//

#include "Command.h"


 void UploadCSV::execute(SharedState* sharedState) {
    // Temporarily store the data from the uploaded CSV files:
    vector<Sample>tempTrain;
    vector<Sample>tempTest;
    // Prompts the user to upload two files, one called "Train.csv" and the other "Test.csv":
     string trainFile="", testFile="",tempTrainFile,tempTestFile;
     int flagTrain=0,flagTest=0;
     dio->write("DanielOrItsCommandOne");
     while(true){
         // Reads the files and concatenates them into strings called Trainfile and Testfile:
         tempTrainFile=dio->readFile();
         trainFile=trainFile+tempTrainFile;
         if(trainFile.find("DanielOrFileDone") != string::npos){
             size_t pos = trainFile.find("DanielOrFileDone");
             trainFile=trainFile.substr(0,pos);
             break;
         }
     }
     // Opens two output file streams, one for "Train.csv" and the other for "Test.csv",
     // and writes the contents of the Trainfile and Testfile strings to them, respectively:
     ofstream trainStream("train.csv");
     trainStream << trainFile;
     trainStream.close();
     tempTrain = readFromFile("train.csv",0);
     if (tempTrain.empty()) {
         dio->write("Invalid input\n");
         flagTrain=-1;
         return;
     }
     dio->write("Upload complete.\n");
     while(true){
         tempTestFile=dio->readFile();
         testFile=testFile+tempTestFile;
         if(testFile.find("DanielOrFileDone") != string::npos){
             size_t pos = testFile.find("DanielOrFileDone");
             testFile=testFile.substr(0,pos);
             break;
         }
     }
     ofstream testStream("test.csv");
     testStream << testFile;
     testStream.close();
     tempTest = readFromFile("test.csv",1);
     if (tempTest.empty()) {
         dio->write("Invalid input\n");
         flagTest=-1;
         return;
     }
     // read the contents of the "Train.csv" and "Test.csv" files and store them in the vectors.
     // If the vectors are empty, the method prompts the user with an error message and returns:

     dio->write("Upload complete.\n");
     if(flagTest==0&&flagTrain==0){
         sharedState->dbTrain=tempTrain;
         sharedState->dbTest=tempTest;
         sharedState->isUpload= true;
     }

}

int Setting::checkKandM(SharedState* sharedState,string message) {/*
 * The function receives the message from the user and checks it.
 * If the input is correct, it returns 0 and keeps the vector, K and the distance function in the class members.
 * If the cell is incorrect, it returns -1.
 */
    int index=-1;//flag
    int kTempInt;
    int flagk=0,flagM=0;
    string distanceTemp="";
    if(message.size()==0){//check if the str empty
        return -3;
    } else {
        for (int i=0;i<message.size();i++) {
            // Go through each character in the string
            //The loop checks the first index where there is a letter and not a number - a sign that we have reached the distance .
            if (isalpha(message[i])){
                index=i;
                break;
            }
        }
        if(index==-1){
            //If the value of the index has not changed, there are no letters in the user's message, meaning there is no distance function and the input is incorrect.
            flagM=-1;
        }
        if(index+2>message.size()-1){
            //If the input is correct, the distance function will have a length of 3 followed by a space and then K. Therefore the condition should be met, if not met the input is incorrect.
            flagM=-1;
        }
        //Dividing the message into variables according to the order in which they are supposed to be:
        string kTemp=message.substr(0,index);
        if(flagM==0){
             distanceTemp= message.substr(index,3);
        }

        //Sending the vector cycle to a function that returns the vector in a vector variable:
        try {
            //Trying to convert K from a string to double
            kTempInt = stoi(kTemp);
        }
        catch (...){
            //If the conversion failed, the input is incorrect
            ;
        }
        if(argumentsCheckClient(distanceTemp,kTempInt)<0){
                return argumentsCheckClient(distanceTemp,kTempInt);
        }


        if(kTempInt>sharedState->dbTrain.size()&&sharedState->isUpload== true){
            //If k is greater than the number of samples it is impossible to do the division and therefore the input is incorrect
            flagk=-1;
        }
        sharedState->k=kTempInt;
        sharedState->distanceM=distanceTemp;
        if (flagk==-1 && flagM==0){
            return -1;
        }
        if (flagk==-1 && flagM==-1){
            return -3;
        }
        if (flagk==0 && flagM==-1){
            return -2;
        }
        return 0;
    }

}

void Setting::execute(SharedState* sharedState) {
    //  Retrieves the current values of k and distanceM  prints them to the user:
    int checkP;
    int k = sharedState->k;
    string distanceM = sharedState->distanceM;
    //  Prompts the user to enter new values for k and distanceM:
    dio->write("The current KNN parameters are: K = " + std::to_string(k) +  ", distance metric = " + distanceM+"\n");
    dio->write("DanielOrYouDone");
    string input = dio->read();
    // Receives a message from the user and  checks if the input is correct:
    if (input!="") {
        checkP= checkKandM(sharedState, input);
        if(checkP<0){
            if(checkP==-1){
                dio->write("invalid value for K\n");
            }
            if(checkP==-2){
                dio->write("invalid value for metric\n");
            }
            if(checkP==-3){
                dio->write("invalid value for K\n");
                dio->write("invalid value for metric\n");
            }
        }

    }

}
// This function handles the process of classifying the data using KNN:
void Classify:: execute(SharedState* sharedState)  {
    //  Checks if the data has been uploaded:
    if (sharedState->isUpload== false) {
        // If the data has not been uploaded, it asks the user with an error message and returns:
        dio->write("please upload data\n");
        return;
    }
    // If the data has been uploaded, it creates a new KNN object:
        Knn answer(sharedState->dbTrain, sharedState->distanceM, sharedState->k);
    // Classify each sample in the dbTest vector (by KNN):
        for(int i=0;i<sharedState->dbTest.size();i++){
            sharedState->dbTest[i].label=answer.findTheLabel(sharedState->dbTest[i].deatils);
        }
        // Prompts the user with a message indicating that the classification is complete successfully:
        dio->write("classifying data complete\n");
        sharedState->isClassify= true;

}

// This function handles the process of displaying the results of the classification:  . , and then . Finally, it .
void DisplayResult:: execute(SharedState* sharedState)  {
    string answer="";
    // Checks if the data has been uploaded and classified:
    if (sharedState->isUpload== false) {
        // If the data has not been uploaded, it prompts the user with an error message and returns:
        dio->write("please upload data\n");
        return;
    }
    if (sharedState->isClassify== false) {
        // If the data has not been classified, it prompts the user with an error message and returns:
        dio->write("please classify the data\n");
        return;
    }
    // If the data has been uploaded and classified,
    // it concatenates the index and the label of each sample in the vector:
    for(int i=0;i<sharedState->dbTest.size();i++){
        answer=to_string(i+1) +" "+ sharedState->dbTest[i].label +"\n";
        dio->write(answer); // sends the concatenated string to the user
    }
    // Prompts the user with a message indicating that the display is complete successfully:
    dio->write("Done.\n");

}

// This function handles the process of downloading the results of the classification:
void DownlandResult::execute(SharedState* sharedState) {
    // Checks if the data has been uploaded and classified:
    if (sharedState->isUpload == false) {
        // // If the data has not been uploaded, it prompts the user with an error message and returns:
        dio->write("please upload data\n");
        return;
    }
    if (sharedState->isClassify == false) {
        // // If the data has not been classified, it prompts the user with an error message and returns:
        dio->write("please classify the data\n");
        return;
    }
    string fileName;
    // Write the results to the file
    string results="";
    // If the data has been uploaded and classified,
    // it concatenates the index and the label of each sample in the vector:
    for (int i = 0; i < sharedState->dbTest.size(); i++) {
        results=results+(to_string(i + 1) + " " + sharedState->dbTest[i].label+"\n");
    }
    // Sends the concatenated string to the user with a message indicating that
    // the writing to file is complete successfully:
    results=results+"Done.DanielOrDoneWriteToFile";
    dio->write(results);

}


void Exit::execute(SharedState* sharedState) {
}

