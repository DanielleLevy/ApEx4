//
// Created by danie on 25/12/2022.
//

#include "Server.h"


Server::Server(int port, string file) {/*
 * The constructor initializes two member variables of the Server class: server_port and db.
 * It sets server_port equal to the port argument .
 * db equal to the result of calling the readFromFile function, passing in the file argument.
 * readFromFile-  read the contents of a file.
 * The constructor also creates a socket file descriptor using the socket function and assigns the file descriptor to the sockFD member variable.
 */
    server_port=port;
    db= readFromFile(file);
    if (db.empty()) {
        //Checks if the file is not empty:
        cout << "invalid input" << endl;
        exit(0);
    }
    sockFD=socket(AF_INET, SOCK_STREAM, 0);
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
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sockFD, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        //bind the socket file descriptor stored in sockFD to the address specified by the sockaddr_in structure sin. If the bind function returns a value less than 0, it indicates an error and the function prints an error message and returns -1.
        cout << "error binding socket" << endl;
        return -1;
    }
    return 0;

}



int Server::handleClientServer() {/*
 *The function listens to the client, receives the input and checks it and finally returns an answer to the client.
 * The function returns 0 if the process was successful and 1 otherwise.
 */
    int sentBytes;
    if (listen(sockFD, 0) < 0) {
        //If the listen function returns a value less than 0, it indicates an error and the function prints an error message and returns -1.
        cout << "error listening to a socket" << endl;
        return -1;
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int clientSock = accept(sockFD, (struct sockaddr *) &client_sin, &addr_len);
    if (clientSock < 0) {
        // If the accept function returns a value less than 0, it indicates an error and the function prints an error message and returns -1.
        cout << "error accepting client" << endl;
        return -1;
    }
    char buffer[4096];
    int expectedDataLen = sizeof(buffer);
    while (true) {
        bzero(buffer, expectedDataLen); //empty the buffer/
        int readBytes = recv(clientSock, buffer, expectedDataLen, 0);
        if (readBytes == 0) {
            //If the recv function returns 0, it indicates that the connection has been closed and the loop is broken.
            cout << "connection is closed" << endl;
            break;
        } else if (readBytes < 0){
            // If the recv function returns a value less than 0, it indicates an error and the function prints an error message and returns -1.
            cout << "error receive" << endl;
            return -1;
        } else {
            //If the recv function returns a value greater than 0, indicating that data has been received, the function calls a function named CheckFromClient on buffer
            int answerCheck = checkFromClient(buffer);
            if (answerCheck == 0) {
                //The input is correct and saved by the members of the class.
                answer = calcServer(vectorToClass, distanceM, k);
            } else if (answerCheck == -1) {
                //invalid input.
                answer = "invalid input";
            }
            sentBytes = send(clientSock, answer.c_str(), answer.length(), 0);
            if (sentBytes < 0) {
                //if send to the client failed.
                cout << "error sending to client" << endl;
                return -1;
            }
        }
    }
    close(clientSock);
    return 0; // all goes well.
}



int Server::checkFromClient(string message) {/*
 * The function receives the message from the user and checks it.
 * If the input is correct, it returns 0 and keeps the vector, K and the distance function in the class members.
 * If the cell is incorrect, it returns -1.
 */
    int index=-1;//flag
    if(message.size()==0){//check if the str empty
        return -1;
    } else {
        for (int i=0;i<message.size();i++) {
            // Go through each character in the string
            //The loop checks the first index where there is a letter and not a number - a sign that we have reached the distance .
            if (isalpha(message[i])){
                index=i;
                break;
            }
        }
        if(index==-1){
            //If the value of the index has not changed, there are no letters in the user's message, meaning there is no distance function and the input is incorrect.
            return -1;
        }
        if(index+4>message.size()-1){
            //If the input is correct, the distance function will have a length of 3 followed by a space and then K. Therefore the condition should be met, if not met the input is incorrect.
            return -1;
        }
        //Dividing the message into variables according to the order in which they are supposed to be:
        string vectorTemp=message.substr(0,index);
        distanceM= message.substr(index,3);
        string kTemp=message.substr(index+4,message.size()-vectorTemp.size()-distanceM.size());
        //Sending the vector cycle to a function that returns the vector in a vector variable:
        vectorToClass = createVector(vectorTemp, ' ');
        if(vectorToClass.empty()){
            //If the vector is empty, it means that the input is incorrect
            return -1;
        }
        try {
            //Trying to convert K from a string to double
            k = stoi(kTemp);
        }
        catch (...){
            //If the conversion failed, the input is incorrect
            return -1;
        }
        if(k>db.size()){
            //If k is greater than the number of samples it is impossible to do the division and therefore the input is incorrect
            return -1;
        }
        if(checkInput(vectorToClass,db[0].vectorSize)<0){
            //Checks whether the vector is the same size as the vectors in the database.
            return -1;
        }
        return 0;
    }

}

string Server::calcServer(vector<double> vectorfromuser, string distance, int k) {
    //The function receives a valid input, creates an instance of KNN and returns the label
    Knn answer(db, distance, k, vectorfromuser);
    return  answer.findTheLabel();
}

int main(int argc, char *argv[]){
    int port;
    try{
      port= stoi(argv[2]); //Converting the port to a number
    }
    catch(...) {
        // Invalid port
        cout<<"invalid input"<<endl;
    }
    if(port<1024 || port>65535){
        //Checking whether the port is within range
        cout<<"invalid input"<<endl;
    }
    Server myServer=Server(port,argv[1]);
    int initAns=myServer.initServer();
    if (initAns==0){
        //check if the server init well
        while (true){
            int talkWClient=myServer.handleClientServer();
            if(talkWClient<0){
                continue;
            }
        }
    }

}







