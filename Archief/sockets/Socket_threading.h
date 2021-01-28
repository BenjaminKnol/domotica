/*
 * TThis file ensures that the Raspberry Pi can listen to multiple
 * connections from clients and receive and / or send data.
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *
 * Used sources: https://www.geeksforgeeks.org/multithreading-in-cpp/     ---> Callable class
 */

#ifndef SOCKET_1_2_SOCKET_THREADING_H
#define SOCKET_1_2_SOCKET_THREADING_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

using namespace std;

class Socket_threading {
public:
    Socket_threading();

    int read_message(string *buf, int length, int child_socket);

    void operator()(string *message, int message_length, int child_socket);
    // First parantheses is callable class.
    // Second paranthese are parameters.
};

#endif //SOCKET_1_2_SOCKET_THREADING_H
