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
    int flagIfCommand8 = 0;
    char buffer[4096];
    int expectedDatalen = sizeof(buffer);
    string inputFromUser,fileName,writeToFile,writeToUser,trainFile,testFile;
    while (flagIfCommand8 == 0) {
        writeToUser="";
        while (true) {
            bzero(buffer, expectedDatalen);
            int readBytes = recv(sockFD, buffer, sizeof(buffer)-1, 0);
            if (readBytes == 0) {
                flagIfCommand8 = -1;
                break;
            } else if (readBytes < 0) {
                return -1;
            } else {
                string bufferString(buffer);
                writeToUser=writeToUser+bufferString;
                if (writeToUser.find("DanielOrItsCommandOne") != string::npos) {
                    writeToUser="";
                     // Read the train file from the local filesystem
                     cout << "Please enter the path of your local train CSV file:\n";
                     getline(cin, trainFile);
                     ifstream trainStream(trainFile);
                     stringstream trainBuffer;
                     trainBuffer << trainStream.rdbuf();
                     string trainContent = trainBuffer.str();
                     // Send the train file contents to the server
                     trainContent=trainContent+"DanielOrFileDone";
                     int sentBytes = send(sockFD, trainContent.c_str(), trainContent.length(), 0);
                     if (sentBytes > 0) {
                         bzero(buffer, expectedDatalen);
                         // Read the test file from the local filesystem
                         int readBytes = recv(sockFD, buffer, sizeof(buffer)-1, 0);
                         if(readBytes>0){
                             cout<<string (buffer);
                             bzero(buffer, expectedDatalen);
                         }
                         else{
                             break;
                         }
                         cout<<"Please enter the path of your local test CSV file:\n";
                         getline(cin, testFile);
                         ifstream testStream(testFile);
                         stringstream testBuffer;
                         testBuffer << testStream.rdbuf();
                         string testContent = testBuffer.str();
                         testContent=testContent+"DanielOrFileDone";
                         // Send the test file contents to the server
                         int sentBytes = send(sockFD, testContent.c_str(), testContent.length(), 0);
                         if(sentBytes<0) {
                             break;
                         } else{
                             int readBytes = recv(sockFD, buffer, sizeof(buffer)-1, 0);
                             if(readBytes>0)
                             {
                                 cout<<string (buffer);
                                 bzero(buffer, expectedDatalen);

                             }
                         }
                     }
                 }
                 else if (writeToUser.find("DanielOrDoneWriteToFile") != string::npos&&writeToUser.find("DanielOrYouDone") != string::npos) {
                    size_t pos = writeToUser.find("DanielOrDoneWriteToFile");
                    writeToFile = writeToUser.substr(0, pos);
                    size_t postoDonePrint = writeToUser.find("DanielOrYouDone");
                    writeToUser= writeToUser.substr(pos+23,postoDonePrint-pos-23);
                    cout<<"Please enter a path to create the file locally.\n";
                    getline(cin,fileName);
                    // Create a new thread to handle the file writing
                    thread t(&Client::writeToFile, this, writeToFile, fileName);
                    t.detach();
                    break;
                }
                else if (writeToUser.find("DanielOrYouDone") != string::npos) {
                    size_t pos = writeToUser.find("DanielOrYouDone");
                    writeToUser = writeToUser.substr(0, pos);
                    break;
                }

            }
        }

        cout<<writeToUser;
        writeToUser="";

        if (flagIfCommand8 == -1) {
            break;
        }
        // Receives input from the user and checks it. If it is normal then the mount should be 0:
        getline(cin, inputFromUser);
        inputFromUser=inputFromUser+"D";
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
