//
// Created by danie on 11/01/2023.
//

#ifndef APEX4_COMMAND_H
#define APEX4_COMMAND_H
using namespace std;
#include <string>
#include "DefaultIO.h"
#include "Sample.h"

struct SharedState{
    vector<Sample> db;
    string answer;
    int k;
    string distanceM;
    vector<double> vectorToClass;
    SharedState(){
        k=5;
        distanceM="AUC";
    }
};
class Command {
protected:
    DefaultIO* dio;
public:
    string description;
    Command(DefaultIO* dio, string des);
    virtual void execute(SharedState* sharedState);
    virtual ~Command(){}

};
class UploadCSV:public Command {
public:
    virtual void execute(SharedState* sharedState);
    UploadCSV(DefaultIO* dio):Command(dio,"upload an unclassified csv datafile"){}
};
class Setting:public Command {
public:
    Setting(DefaultIO* dio): Command(dio,"algorithm settings"){};
    virtual void execute(SharedState* sharedState);

};
class Classify: public Command {
public:
    Classify(DefaultIO* dio): Command(dio,"classify data"){};
    virtual void execute(SharedState* sharedState);

};
class DisplayResult: public Command {
public:
    DisplayResult(DefaultIO* dio): Command(dio,"display results"){};
    virtual void execute(SharedState* sharedState);

};
class DownlandResult:public Command {
public:
    DownlandResult(DefaultIO* dio): Command(dio,"download results"){};
    virtual void execute(SharedState* sharedState);

};
class Exit:public Command {
public:
    Exit(DefaultIO* dio): Command(dio,"exit"){};
    virtual void execute(SharedState* sharedState);

};


#endif //APEX4_COMMAND_H
