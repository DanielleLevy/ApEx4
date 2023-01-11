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

using namespace std;

class Server {
protected:
    int server_port ;
    int sockFD ;
    int k;
    string distanceM;
    vector<double> vectorToClass;
    string calcServer(vector<double> vectorfromuser, string distance, int k);
    int checkFromClient(string message);



public:
    vector<Sample> db;
    string answer;
    Server(int port, string file);
    int initServer();
    int handleClientServer();
};


#endif //UNTITLED1_SERVER_H
