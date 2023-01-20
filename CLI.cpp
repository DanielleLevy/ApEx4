

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

void CLI::start() {
    SharedState sharedState;
    string menu;
    int index = -1;
    while (index != 5) {
        menu="Welcome to the KNN Classifier Server. Please choose an option:\n";
        for (size_t i = 0; i < commandsToExe.size() - 1; i++) {
            string s("1.");
            s[0] = ((char) (i + 1 + '0'));
            menu=menu+s;
            menu=menu+commandsToExe[i]->description + "\n";
        }
        menu=menu+"8.";
        menu=menu+commandsToExe[5]->description + "\n";
        menu=menu+"DanielOrYouDone";
        dio->write(menu);
        string input = dio->read();
        index = input[0] - '0' - 1;
        if ((index >= 0 && index <= 4) || index == 7) {
            if (index == 7) {
                index = 5;
            }
            commandsToExe[index]->execute(&sharedState);
        }
    }
}

CLI::~CLI() {
    for(size_t i=0;i<commandsToExe.size();i++){
        if(commandsToExe[i]!=nullptr)
            delete commandsToExe[i];
    }
}



/*int main(int argc, char *argv[]){
    DefaultIO* sio  = new StandardIO;
    CLI cli(sio);
    cli.start();


}*/