//
// Created by danie on 06/12/2022.
//


#include "Header.h"
using namespace std;

vector<Sample> readFromFile(string fileName){
    /**
     * The function receives the name of the file and reads from it.
     * The function returns a vector of examples where each is an instance of the classifier.
     */
    vector<Sample> db; //The vector that is finally returned
    vector<string> row; //A vector that holds each line in the file.
    vector<double> detail; //A vector that will hold the numbers for each example.
    string line, word,label;
    int size, startSize,counter=0;
    string nameFile=fileName;
    fstream file (nameFile, ios::in);
    if(file.is_open())
    {
        //Checks if the file can be opened
        while(getline(file, line))
        {
            //Reads line by line from the file.
            row.clear();    //Clearing the vectors from the previous row.
            detail.clear(); //Clearing the vectors from the previous row.
            stringstream str(line);
            while(getline(str, word, ','))
                //Inserts each word in the line as a variable in the vector.
                row.push_back(word);
            size= row.size()-1; //Subtracts the last value from the size and this is the size of the measurements.
            if(counter==0){
                //Checks if this is the first vector, if so saves its size and compares it with the size of all the other vectors in the file.
                startSize=size;
            }
            if(startSize!=size){
                //If a vector is found that does not match in size, the program prints an error and exits.
                cout<<"The file contains vectors of different length, try another file."<<endl;
                exit(0);
            }
            label=row.back();   //Saves the label.
            for (int i=0;i<row.size()-1;i++){
                //Converts the vector from a string to double.
                try{
                    //input check if its contains string
                    double value=stod(row[i]);
                    detail.push_back(value);
                }
                catch(...){
                    cout<<"the vector should contain numbers only, try another file"<<endl;
                    exit(0);
                }
            }
            //Generates an example and puts it in the examples vector.
            Sample a= Sample(size,detail,label);
            db.push_back(a);
            counter++;  //Raises the counter
        }
        return db;
    }
    else
        //If the file does not open
        cout<<"Could not open the file\n";
    return db;
}
vector <double> createVector(string str, char seprate) {
        /*this function get create a vector from the input
         * input: str- the line that the user put
         *        seprate- A character that tells us how the numbers are separated
         * output: vector full with numbers, if the input was ok*/

        vector<double> v;
        vector<double> invalidVector;// if the input invalid, return an empty vector.
        if(str.size()==0){//check if the str empty
            return invalidVector;
        }
        string number;  //holds the number until the next seprate
        double numberAfterConv;    // wiil hold the number to insert to the vector
        for (int i=0;i<str.size();i++){     // Go through each character in the string
            if(isalpha(str[i]) ){           //Checks if the character is a letter
                return invalidVector;
            }
            if (str[i]!=seprate){       //Checks whether the character isn't the separator character (in this case a space)
                number=number+str[i];   //If we haven't reached the separator character, it adds the character to the number
            }
            else if(number.size()!=0 && str[i]==seprate){   //Checks whether we have reached the separator character and there is content in the number
                try{
                    numberAfterConv=stod(number); //Converting a string to a number
                }
                catch(...){
                    //If the conversion was not successful, it was probably not a number: prints an error and exits the program
                    return invalidVector;
                }
                v.push_back(numberAfterConv);   //If the conversion was successful, pushes the number into the vector
                number.clear(); //If the conversion was successful, pushes the number into the vector
            }
            else{
                //If we have reached a space but there is no value for the number, we will continue until there is a character that is not a space
                continue;
            }
        }
        if(number.size()!=0) {
            //If there is a last number that is not followed by a space, a check is made on it and it is inserted into the vector
            try{
                numberAfterConv=stod(number);
            }
            catch(...){
                return invalidVector;
            }
            v.push_back(numberAfterConv);
        }
        return v;   //Returning the vector
    }
    int checkInput(vector <double> vector1,int size){
        //The function receives vector and the expected size of the vector
        if (vector1.size()!=size){
            //The vector is not the required size
            return -1;
        }
        if (vector1.size()==0){
            //If the magnitude of one of the vectors is equal to 0
            return -1;
        }
        return 0;
    }


int argumentsCheckClient (string distance, int k){

    // Checking input on the distance function type. It must be one of the five known functions.
    // Otherwise, you will print an error message and exit the program:
    if(distance != "AUC" && distance != "MAN" && distance != "CHB" && distance != "CAN" && distance != "MIN") {
        return -1;
    }

    // Checking input on K. K must be a positive integer,
    // otherwise you will print an error message and exit the program:
    if(k < 1 ) {
        return -1;
    }
    return 0;

}





