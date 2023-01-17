//
// Created by danie on 25/12/2022.
//

#ifndef UNTITLED1_SERVER_H
#define UNTITLED1_SERVER_H
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "Sample.h"
#include "Knn.h"
#include "Header.h"
#include <threads.h>
#include "thread"
#include "pthread.h"
#include "DefaultIO.h"
#include "CLI.h"


using namespace std;

class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};

class ManagerClients:public ClientHandler{
public:
    virtual void handle(int clientID){
        SocketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
    }
};
class Server {
protected:
    int serverPort;
    int sockFD ;
    int k;
    string distanceM;
    vector<double> vectorToClass;
    int checkFromClient(string message);
    sockaddr_in server;
    sockaddr_in client;

    thread* t;

    volatile bool stopped;



public:
    vector<Sample> db;
    string answer;
    Server(int port);
    int initServer();
    int handleClientServer();
    virtual ~Server();
    void stop();
    void start(ClientHandler& ch)throw(const char*);

};


#endif //UNTITLED1_SERVER_H
