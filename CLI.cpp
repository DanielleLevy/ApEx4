//
// Created by danie on 12/01/2023.
//

#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio=dio;
    commandsToExe.push_back(new UploadCSV(dio));
    commandsToExe.push_back(new Setting(dio));
    commandsToExe.push_back(new Classify(dio));
    commandsToExe.push_back(new DisplayResult(dio));
    commandsToExe.push_back(new DownlandResult(dio));
    commandsToExe.push_back(new Exit(dio));
}

void CLI::start(){
    SharedState sharedState;
    int index=-1;
    while(index!=5){
        dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
        for(size_t i=0;i<commandsToExe.size();i++){
            string s("1.");
            s[0]=((char)(i+1+'0'));
            dio->write(s);
            dio->write(commandsToExe[i]->description+"\n");
        }
        string input = dio->read();
        index=input[0]-'0'-1;
        if(index>=0 && index<=6)
            commandsToExe[index]->execute(&sharedState);
    }
}


CLI::~CLI() {
    for(size_t i=0;i<commandsToExe.size();i++){
        delete commandsToExe[i];
    }
}
