//
// Created by danie on 11/01/2023.
//

#include "DefaultIO.h"



// This function reads data from the socket and returns it as a string:
string SocketIO::read(){
    // read data from the socket into a buffer:
    char buffer [4096];
    int expectedDatalen = sizeof(buffer);
    // converts the buffer to a string:
    bzero(buffer, expectedDatalen);
    if (recv(clientID, buffer, sizeof(buffer)-1, 0)) {
        string answer=string(buffer);
        answer=answer.substr(0,answer.find("D")); // removes anything after the substring "D"
        return answer;
    } else {
        return "";
    }
}

// This function reads data from the socket and returns it as a string:
 string SocketIO::readFile(){
     char c=0;
     string s="";
     // read data from the socket into a buffer:
     char buffer [4096]={0};
     int expectedDatalen = sizeof(buffer);
     bzero(buffer, expectedDatalen);
     int readBytes=recv(clientID, buffer, expectedDatalen-1, 0);
     if (readBytes <= 0) {
         return s;
     } else {
         // converts the buffer to a string and returns it:
         for (int i = 0; i < expectedDatalen-1; i++) {
             c = buffer[i];
             if (c == '\0') {
                 break;
             } else {
                 s += c;
             }
         }
     }
    return s;
}
// This function writes the given text to the socket:
void SocketIO::write(string text){
    const char* txt=text.c_str();
    send(clientID,txt,strlen(txt),0);
}

