

#include "CLI.h"
/*This code defines a Command Line Interface (CLI) class for a K-Nearest Neighbors (KNN) classifier server.*/
CLI::CLI(DefaultIO* dio) {/*
 * The CLI constructor takes a DefaultIO object as input and uses it to initialize a vector of command objects.
 * These command objects include:
 * UploadCSV: for uploading a CSV file
 * Setting: for setting various parameters for the KNN classifier
 * Classify: for running the classification on the uploaded data
 * DisplayResult: for displaying the classification results
 * DownlandResult: for downloading the classification results
 * Exit: for exiting the CLI
 */
    this->dio=dio;
    commandsToExe.push_back(new UploadCSV(dio));
    commandsToExe.push_back(new Setting(dio));
    commandsToExe.push_back(new Classify(dio));
    commandsToExe.push_back(new DisplayResult(dio));
    commandsToExe.push_back(new DownlandResult(dio));
    commandsToExe.push_back(new Exit(dio));
}

void CLI::start() {/*
 * The start() method of the CLI class is used to start the CLI.
 * It displays a menu of options to the user, reads their input, and then executes the corresponding command.
 * The SharedState class is used to share data between different commands.
 */
    SharedState sharedState;
    string menu;
    int index = -1;
    while (index != 5) {
        menu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
        for (size_t i = 0; i < commandsToExe.size() - 1; i++) {
            string s("1.");
            s[0] = ((char) (i + 1 + '0'));
            menu = menu + s;
            menu = menu + commandsToExe[i]->description + "\n";
        }
        menu = menu + "8.";
        menu = menu + commandsToExe[5]->description + "\n";
        menu = menu + "DanielOrYouDone"; //end string- sign the the client receive all the information.
        dio->write(menu);
        cout<<"BEFORE\n";
        string input = dio->read();
        cout<<"AFTER"<<endl;
        if (input.size() > 1) {
            //the number should be 1-5 or 8
            dio->write("invalid input\n");
        } else {
            index = input[0] - '0' - 1;
            if ((index >= 0 && index <= 4) || index == 7) {
                if (index == 7) {
                    index = 5;
                }
                commandsToExe[index]->execute(&sharedState);
            } else {
                dio->write("invalid input\n");
            }
        }
    }
}

CLI::~CLI() {
    //The ~CLI() destructor is used to free up the memory allocated for the command objects.
    for(size_t i=0;i<commandsToExe.size();i++){
        if(commandsToExe[i]!=nullptr)
            delete commandsToExe[i];
    }
}



