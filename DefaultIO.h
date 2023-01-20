//
// Created by danie on 11/01/2023.
//

#ifndef APEX4_DEFAULTIO_H
#define APEX4_DEFAULTIO_H
#include <string.h>
#include "iostream"
#include <sys/socket.h>
#include <sstream>
using namespace std;

class DefaultIO {
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual string readFile() = 0;
    virtual ~DefaultIO(){}

};

class StandardIO : public DefaultIO {
public:
    StandardIO();
    void write(string text) override ;
    string read() override;
    string readFile() ;

};
class SocketIO : public DefaultIO {
   int clientID;
public:

    SocketIO(int clientID):clientID(clientID){}
    virtual string read();
    virtual void write(string text);
    string readFile() ;
};





#endif //APEX4_DEFAULTIO_H
