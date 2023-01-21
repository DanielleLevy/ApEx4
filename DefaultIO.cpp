//
// Created by danie on 11/01/2023.
//

#include "DefaultIO.h"

/*StandardIO::StandardIO()
{}


void StandardIO:: write(string text) {
    cout << text;
}
string StandardIO::read(){
    string s;
    getline(cin, s);
    return s;
}

string StandardIO::readFile(){
    string s;
    getline(cin, s);
    return s;
}*/

string SocketIO::read(){
    char buffer [4096];
    int expectedDatalen = sizeof(buffer);
    bzero(buffer, expectedDatalen);
    if (recv(clientID, buffer, sizeof(buffer)-1, 0)) {
        string answer=string(buffer);
        answer=answer.substr(0,answer.find("D"));
        return answer;
    } else {
        return "";
    }
}


 string SocketIO::readFile(){
     char c=0;
     string s="";
     char buffer [4096]={0};
     int expectedDatalen = sizeof(buffer);
     bzero(buffer, expectedDatalen);
     int readBytes=recv(clientID, buffer, expectedDatalen-1, 0);
     if (readBytes <= 0) {
         return s;
     } else {
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
void SocketIO::write(string text){
    const char* txt=text.c_str();
    send(clientID,txt,strlen(txt),0);
}

