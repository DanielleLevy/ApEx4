//
// Created by danie on 12/01/2023.
//

#ifndef APEX4_CLI_H
#define APEX4_CLI_H


#include <vector>
#include <algorithm>
#include <string.h>
#include "Command.h"
#include "DefaultIO.h"
using namespace std;
class CLI {
    vector<Command*> commandsToExe;
        DefaultIO* dio;
    public:
        CLI(DefaultIO* dio);
        void start();
        virtual ~CLI();

    CLI();
};


#endif //APEX4_CLI_H
