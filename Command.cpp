//
// Created by danie on 11/01/2023.
//

#include "Command.h"
Command::Command(DefaultIO* dio,string des) {
    dio=dio;
    description=des;
}

 void UploadCSV::execute() {
     string testFile;
     dio->write("Please upload your local train CSV file.\n");
     dio->read(testFile);
     dio->write("Upload complete.\n");
     dio->write("Please upload your local test CSV file.\n");
     dio->read(testFile);
     dio->write("Upload complete.\n");

}



void Setting::execute() {
}

void Classify:: execute()  {


}
void DisplayResult:: execute()  {
}
void DownlandResult:: execute() {

}
void Exit::execute() {
}
