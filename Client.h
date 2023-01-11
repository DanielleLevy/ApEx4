//
// Created by Or Gabay on 27/12/2022.
//

#ifndef APEX3_CLIENT_H
#define APEX3_CLIENT_H
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


class Client {
protected:
    char * serverIp;
    int clientPort;
    int sockFD;
    int checkFromUser(string message);
public:
    bool checkingIp();
    bool checkingPort();
    int initClient();
    int handleServerClient();
    Client(char * ip, int port);
};


#endif //APEX3_CLIENT_H
