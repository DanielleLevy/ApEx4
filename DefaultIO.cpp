//
// Created by danie on 11/01/2023.
//

#include "DefaultIO.h"
using namespace std;




    void StandardIO:: read(string & out) {
        // Read from standard input
        getline(cin, out);
    }
    void StandardIO:: write(const std::string & in) {
        // Write to standard output
        cout<<in;
    }



    void SocketIO::read(std::string & out) {
        char buffer[4096];
        // Read from socket
        int len = recv(sockfd, buffer, 4096, 0);
        buffer[len] = '\0';
        out = buffer;
    }

    void SocketIO::write(const std::string & in) {
        // Write to socket
        send(sockfd, in.c_str(), in.size(), 0);
    }