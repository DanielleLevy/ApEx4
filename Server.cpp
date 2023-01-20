//
// Created by danie on 25/12/2022.
//

#include "Server.h"


Server::Server(int port) {/*
 * The constructor initializes one member  of the Server class: server_port .
 * It sets server_port equal to the port argument .
 * db equal to the result of calling the readFromFile function, passing in the file argument.
 * readFromFile-  read the contents of a file.
 * The constructor also creates a socket file descriptor using the socket function and assigns the file descriptor to the sockFD member variable.
 */
    serverPort=port;
    sockFD=socket(AF_INET, SOCK_STREAM, 0);
    stopped=false;
}
int Server:: initServer(){/*
 * The function initializes the server
 * returning 0 if the initialization was successful and 1 if not
 */
    if (sockFD < 0){
        // check if the sockFD member variable is less than 0. If it is, it prints an error message and returns -1.
        cout<<"error creating socket"<<endl;
        return -1;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(serverPort);
    if (bind(sockFD, (struct sockaddr *) &server, sizeof(server)) < 0) {
        //bind the socket file descriptor stored in sockFD to the address specified by the sockaddr_in structure sin. If the bind function returns a value less than 0, it indicates an error and the function prints an error message and returns -1.
        cout << "error binding socket" << endl;
        return -1;
    }
    return 0;

}
int Server::handleClientServer() {
    ClientHandler* clientHandler = new ManagerClients();
    if (listen(sockFD, 5) < 0) {
        cout << "error listening to a socket" << endl;
        return -1;
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    while (!stopped) {
        int clientSock = accept(sockFD, (struct sockaddr *) &client_sin, &addr_len);
        if (clientSock < 0) {
            cout << "error accepting client" << endl;
        } else {
            // Create a new thread to handle the client
            std::thread t(&Server::handleClient, this, clientSock, clientHandler);
            t.detach();
        }
    }
    delete clientHandler;
}

void Server::handleClient(int clientSock, ClientHandler* clientHandler) {
    clientHandler->handle(clientSock);
    close(clientSock);
}


Server::~Server() {
}


int main(int argc, char *argv[]){
    int port;
    try{
        port= stoi(argv[1]); //Converting the port to a number
    }
    catch(...) {
        // Invalid port
        cout<<"invalid input"<<endl;
    }
    if(port<1024 || port>65535){
        //Checking whether the port is within range
        cout<<"invalid input"<<endl;
    }
    Server myServer=Server(port);
    int initAns=myServer.initServer();
    if (initAns==0){
        //check if the server init well
        myServer.handleClientServer();
    }
}








