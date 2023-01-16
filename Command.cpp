//
// Created by danie on 11/01/2023.
//

#include "Command.h"


 void UploadCSV::execute(SharedState* sharedState) {
     string trainFile, testFile;
     dio->write("Please upload your local train CSV file.\n");
     trainFile=dio->read();

     sharedState->dbTrain = readFromFile(trainFile,0);
     if (sharedState->dbTrain.empty()) {
         dio->write("Invalid input\n");
         return;
     }

     dio->write("Upload complete.\n");

     dio->write("Please upload your local test CSV file.\n");
     testFile=dio->read();
    sharedState->dbTest = readFromFile(testFile,1);
     if (sharedState->dbTest.empty()) {
         dio->write("Invalid input");
         return;
     }

     dio->write("Upload complete.\n");
     // use the trainSamples and testSamples vectors to train and test the classifier
     sharedState->isUpload= true;

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
    int checkP;
    int k = sharedState->k;
    string distanceM = sharedState->distanceM;
    dio->write("The current KNN parameters are: K = " + std::to_string(k) +  ", distance metric = " + distanceM+"\n");
    string input = dio->read();
    if (input != "") {
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

void Classify:: execute(SharedState* sharedState)  {
    if (sharedState->isUpload== false) {
        dio->write("please upload data\n");
        return;
    }
        Knn answer(sharedState->dbTrain, sharedState->distanceM, sharedState->k);
        for(int i=0;i<sharedState->dbTest.size();i++){
            sharedState->dbTest[i].label=answer.findTheLabel(sharedState->dbTest[i].deatils);
        }
        dio->write("classifying data complete\n");
        sharedState->isClassify= true;

}
void DisplayResult:: execute(SharedState* sharedState)  {
    string answer="";
    if (sharedState->isUpload== false) {
        dio->write("please upload data\n");
        return;
    }
    if (sharedState->isClassify== false) {
        dio->write("please classify the data\n");
        return;
    }
    for(int i=0;i<sharedState->dbTest.size();i++){
        answer=to_string(i+1) +" "+ sharedState->dbTest[i].label +"\n";
        dio->write(answer);
    }
    dio->write("Done.\n");

}
void DownlandResult::execute(SharedState* sharedState) {
    if (sharedState->isUpload == false) {
        dio->write("please upload data\n");
        return;
    }
    if (sharedState->isClassify == false) {
        dio->write("please classify the data\n");
        return;
    }
    string fileName;
    dio->write("Please enter a path to create the file locally.\n");
    fileName = dio->read();

    // Open the file for writing
    std::ofstream out(fileName);
    if (!out) {
        dio->write("Error: Could not open file for writing.\n");
        return;
    }

    // Write the results to the file
    vector<string> results;
    for (int i = 0; i < sharedState->dbTest.size(); i++) {
        results.push_back(to_string(i + 1) + " " + sharedState->dbTest[i].label);
    }
    results.push_back("Done.");
    for (auto &result: results) {
        out << result << std::endl;
    }

    out.close();

}


void Exit::execute(SharedState* sharedState) {
    exit(0);
}

