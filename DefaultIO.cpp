//
// Created by danie on 11/01/2023.
//

#include "DefaultIO.h"

StandardIO::StandardIO()
{}


void StandardIO:: write(string text) {
    cout << text;
}
string StandardIO::read(){
    string s;
    getline(cin, s);
    return s;
}


 string SocketIO::read(){
     char c=0;
     string s="";
     char buffer [4096];
     int expectedDatalen = sizeof(buffer);
     bzero(buffer, expectedDatalen);
     int readBytes=recv(clientID, buffer, sizeof(buffer), 0);
     if (readBytes <= 0) {
         return s;
     } else {
         for (int i = 0; i < expectedDatalen; i++) {
             c = buffer[i];
             if (c == '\000') {
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

void SocketIO::write(float f){
    ostringstream ss;
    ss <<f;
    string s(ss.str());
    write(s);
}
