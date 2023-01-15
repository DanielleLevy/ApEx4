//
// Created by danie on 11/01/2023.
//

#ifndef APEX4_DEFAULTIO_H
#define APEX4_DEFAULTIO_H
using namespace std;
#include <string>
#include "iostream"
#include <sys/socket.h>


class DefaultIO {
public:
    virtual void read(string & out) = 0;
    virtual void write(const string & in) = 0;
};

class StandardIO : public DefaultIO {
public:
    void read(string & out);
    void write(const std::string & in) ;
};
class SocketIO : public DefaultIO {
private:
    int sockfd;

public:
    SocketIO(int fd) : sockfd(fd);

    void read(std::string & out);
    void write(const std::string & in);
};




#endif //APEX4_DEFAULTIO_H
