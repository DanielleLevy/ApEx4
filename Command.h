//
// Created by danie on 11/01/2023.
//

#ifndef APEX4_COMMAND_H
#define APEX4_COMMAND_H
using namespace std;
#include <string>
#include "DefaultIO.h"
#include "Sample.h"
class Command {
protected:
    DefaultIO* dio;
public:
    string description;
    Command(DefaultIO* dio, string des);
    virtual void execute();
    virtual ~Command(){}

};
struct SharedState{
    vector<Sample> db;
    string answer;
    float threshold;
    int testFileSize;
    int k;
    string distanceM;
    vector<double> vectorToClass;
    SharedState(){
        k=5;
        distanceM="AUC";
    }
};
class UploadCSV:public Command {
    UploadCSV(DefaultIO* dio):Command(dio,"upload an unclassified csv datafile"){};
    virtual void execute();

};
class Setting:public Command {
    Setting(DefaultIO* dio): Command(dio,"algorithm settings"){};
    virtual void execute();

};
class Classify: public Command {
    Classify(DefaultIO* dio): Command(dio,"classify data"){};
    virtual void execute();

};
class DisplayResult: public Command {
    DisplayResult(DefaultIO* dio): Command(dio,"display results"){};
    virtual void execute();

};
class DownlandResult:public Command {
    DownlandResult(DefaultIO* dio): Command(dio,"download results"){};
    virtual void execute();

};
class Exit:public Command {
    Exit(DefaultIO* dio): Command(dio,"exit"){};
    virtual void execute();

};


#endif //APEX4_COMMAND_H
