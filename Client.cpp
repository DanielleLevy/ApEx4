//
// Created by Or Gabay on 27/12/2022.
//

#include "Client.h"




Client::Client(char * ip, int port) {
    // This is a constructor for the "Client" class. The constructor initializes two variables
    // IP + PORT. And also creates a new socket:
    serverIp = ip;
    clientPort=port;
    sockFD=socket(AF_INET, SOCK_STREAM, 0);
}


int Client::handleServerClient () {
    int flag = 0;
    char buffer[4096];
    int expectedDatalen = sizeof(buffer);
    string inputFromUser,fileName;
    while (flag == 0) {
        while (true) {
            bzero(buffer, expectedDatalen);
            int readBytes = recv(sockFD, buffer, sizeof(buffer), 0);
            if (readBytes == 0) {
                flag = -1;
                break;
            } else if (readBytes < 0) {
                return -1;
            } else {
                string bufferString(buffer);
                if (bufferString.find("DanielOrYouDone") != string::npos) {
                    size_t pos = bufferString.find("DanielOrYouDone");
                    string substring = bufferString.substr(0, pos);
                    cout << substring;
                    break;
                }
                if (bufferString.find("DanielOrDoneWriteToFile") != string::npos) {
                    size_t pos = bufferString.find("DanielOrDoneWriteToFile");
                    string substring = bufferString.substr(0, pos);
                    cout<<"Please enter a path to create the file locally.\n";
                    getline(cin,fileName);
                    // Create a new thread to handle the file writing
                    std::thread t(&Client::writeToFile, this, substring, fileName);
                    t.detach();
                } else{
                    cout << bufferString;
                }
            }
        }
        if (flag == -1) {
            break;
        }
        // Receives input from the user and checks it. If it is normal then the mount should be 0:
        getline(cin, inputFromUser);
        int sentBytes = send(sockFD, inputFromUser.c_str(), inputFromUser.length(), 0);
        if (sentBytes < 0) {
            return -1;
        }
    }
    close(sockFD);
    return 0;
}

void Client::writeToFile(string contents, string fileName) {
    // Open the file for writing
    std::ofstream out(fileName);
    if (!out) {
        cout << "Error:Could not open file for writing.\n";
        return;
    }
// Write the contents to the file
    out << contents << std::endl;

    out.close();
}


    int Client::initClient() {
    // This function creates a new socket. It verifies that it is possible to create a socket and connect to the server.
    // If everything is normal, it returns 0, if it fails to create a socket or connect to the server,
    // it returns -1 and prints an error message accordingly:

    if (sockFD < 0) {
        cout << "error creating socket" << endl;
        return -1;
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverIp);
    sin.sin_port = htons(clientPort);
    if (connect(sockFD, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error connecting to server" << endl;
        return -1;
    }
    return 0;
}
int main(int argc, char* argv[]) {
    // Receiving the ip and port arguments and checking their correctness:

    Client myClient = Client("127.0.0.1", 55555);
    int initClient =  myClient.initClient();
    if (initClient ==0) {
        // check if the client init well
        while (true) {
            int talkWServer = myClient.handleServerClient();
            if (talkWServer < 0) {
                continue;
            } else{
                break;
            }
        }
    }
}
