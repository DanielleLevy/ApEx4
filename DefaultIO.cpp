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


//string SocketIO::read(){
//    char c=0;
//    size_t i=0;
//    string s="";
//    while(c!='\n'){
//        recv(clientID,&c,sizeof(char),0);
//        s+=c;
//    }
//    return s;
//}
//void SocketIO::write(string text){
//    const char* txt=text.c_str();
//    send(clientID,txt,strlen(txt),0);
//}
//
//void SocketIO::write(float f){
//    ostringstream ss;
//    ss <<f;
//    string s(ss.str());
//    write(s);
//}
//void StandardIO::write(float f){
//    ostringstream ss;
//    ss <<f;
//    string s(ss.str());
//    write(s);
//}