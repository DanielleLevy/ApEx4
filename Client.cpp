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

bool Client::checkingIp(){
    // This is a function that checks whether the IP is correct, that is, it divides it into 4 parts
    // separated by 3 points and checks whether the IP is correct (between 0 and 255).
    // The function returns TRUE if everything is normal, and FALSE if the ip is not normal:
    
    char * analyzeIp = new char[32];
    string ipSection[4];
    int theIndex = 0;
    for (int i = 0; i< strlen(serverIp); i++){
        if (serverIp[i]=='.'){
            theIndex++;
            continue;
        }
        ipSection[theIndex] += serverIp[i];
    }

    for (int j = 0; j<4; j++) {
        int digitsIp;
        try { digitsIp = stoi (ipSection[j]);}
        catch (...){return false;}
        if (digitsIp <0 || digitsIp >255) return false;
    }
    char buffer1[32];
    sprintf(buffer1, "%d", std::stoi(ipSection[0]));
    char buffer2[32];
    sprintf(buffer2, "%d", std::stoi(ipSection[1]));
    char buffer3[32];
    sprintf(buffer3, "%d", std::stoi(ipSection[2]));
    char buffer4[32];
    sprintf(buffer4, "%d", std::stoi(ipSection[3]));
    strcpy(analyzeIp, buffer1);
    strcat(analyzeIp, ".");
    strcat(analyzeIp, buffer2);
    strcat(analyzeIp, ".");
    strcat(analyzeIp, buffer3);
    strcat(analyzeIp, ".");
    strcat(analyzeIp, buffer4);

    return true;
}

bool Client::checkingPort(){
    // This is a function that checks whether the port is correct,
    // i.e. whether it is between 1024 and 65535.
    // If everything is fine then it returns TRUE and if there is a problem then it returns FALSE:
    
    if (clientPort <1024 || clientPort>65535) return false;
    return true;
}

int Client::handleServerClient (){
    // This function connects the client to the server by the socket. If everything is fine, it returns 0:
    string inputFromUser;
    // Receives input from the user and checks it. If it is normal then the mount should be 0:
    getline (cin, inputFromUser);
    int answerCheck = checkFromUser(inputFromUser);
    // If the input is correct, send to the server. If unable to send to server, return -1 and print an appropriate error message:
    if (answerCheck == 0) {
        int sentBytes = send (sockFD, inputFromUser.c_str(), inputFromUser.length(), 0);
        if (sentBytes < 0) {
            cout << "error sending to server" << endl;
            return -1;
        }
    } else if (answerCheck == 1) {
        // If the input is "-1" then close the socket and exit the program:
        close (sockFD);
        exit(0);
    }
    else if (answerCheck == -1){
        // If the input is incorrect then return -1 and print an appropriate error message:
        cout << "invalid input" << endl;
        return -1;
    }
    // Try to read a message you will receive from the server.
    // If the socket and connection is closed you will print an appropriate error message and return 0.
    // If you failed to read or there is a problem you will print an appropriate error message and return -1.
    // If you were able to read the message you received from the server and it is correct, then print it:

    char buffer [4096];
    int expectedDatalen = sizeof(buffer);
    bzero(buffer, expectedDatalen);
    int readBytes = recv(sockFD, buffer, sizeof(buffer), 0);
    if (readBytes == 0) {
        cout << "connection is closed" << endl;
        return 0;
    }
    else if (readBytes < 0) {
        cout<<"error receiving message" << endl;
        return -1;
    }
    else{
        cout << buffer << endl;
    }

return 0;
}

int Client::initClient(){
    // This function creates a new socket. It verifies that it is possible to create a socket and connect to the server.
    // If everything is normal, it returns 0, if it fails to create a socket or connect to the server,
    // it returns -1 and prints an error message accordingly:

        if (sockFD < 0){
            cout<<"error creating socket"<<endl;
            return -1;
        }
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));

        sin.sin_family= AF_INET;
        sin.sin_addr.s_addr = inet_addr(serverIp);
        sin.sin_port = htons(clientPort);
        if (connect(sockFD, (struct sockaddr*)&sin, sizeof(sin))<0)
        {
            cout<<"error connecting to server"<< endl;
            return -1;
        }
return 0;

}

int Client::checkFromUser(string message){
    // The function receives a string from the user and checks if it is correct, if correct returns 0:
    int index=-1;
    if(message.size()==0){//check if the str empty
        return -1;
    }
    else if(message=="-1"){ //check if the input is "-1" - return 1 
        return 1;
    } else{
        for (int i=0;i<message.size();i++) {// Go through each character in the string
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
        string vectorTemp=message.substr(0,index);
        if(index+4>message.size()-1){
             //If the input is correct, the distance function will have a length of 3 followed by a space and then K. Therefore the condition should be met, if not met the input is incorrect.
            return -1;
        }
        //Dividing the message into variables according to the order in which they are supposed to be:
        string distanceT= message.substr(index,3);
        string kTemp=message.substr(index+4,message.size()-vectorTemp.size()-distanceT.size());
        //Sending the vector cycle to a function that returns the vector in a vector variable:
        vector<double> a = createVector(vectorTemp, ' ');
        if(a.empty()){
            //If the vector is empty, it means that the input is incorrect
            return -1;
        }
        try {
            //Trying to convert K 
            int k = stoi(kTemp);
            if(argumentsCheckClient(distanceT,k)==-1){
                return -1;
            }
            return 0;
        }
        catch (...){
            //If the conversion failed, the input is incorrect
            return -1;
        }
    }

}

int main(int argc, char* argv[]) {
    // Receiving the ip and port arguments and checking their correctness:

    Client myClient = Client(argv[1], stoi(argv[2]));
    if (!myClient.checkingIp()) {
        cout << "invalid input";
        exit(0);
    }
    if (!myClient.checkingPort()) {
        cout << "invalid input";
        exit(0);
    }
    int initClient =  myClient.initClient();
    if (initClient ==0) {
        // check if the client init well
        while (true) {
            int talkWServer = myClient.handleServerClient();
            if (talkWServer < 0) {
                continue;
            }
        }
    }
}
