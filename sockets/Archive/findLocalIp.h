//
// Created by benja on 08/01/2021.
//

#ifndef SOCKETS_FINDLOCALIP_H
#define SOCKETS_FINDLOCALIP_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class findLocalIp {
public:
    string findIp();
};


#endif //SOCKETS_FINDLOCALIP_H
