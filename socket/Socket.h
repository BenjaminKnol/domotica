/*
 * This file  ensures that the Raspberry Pi listen to the
 * connection from the Wemos D1 mini devices.
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *
 * Used sources: https://www.bogotobogo.com/cplusplus/sockets_server_client.php  ---> Socket explanation.
 */

#ifndef SOCKET_1_2_SOCKET_SERVER_H
#define SOCKET_1_2_SOCKET_SERVER_H

#include <iostream>
#include <unistd.h> // Used for calling close() function
#include <fstream> // Read from file
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

// Libraries for socket
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Classes
#include "Components/Base/Component.h"

using namespace std;

// Constants
#define MESSAGE_LENGTH 256
#define NETWORK_QUEUE 8
#define PORT 9002

class Socket {
public:
    Socket(); // Default constructor

    // Do-function
    void createSocket();
    void listenToClient();
    void sendMessage(char*, int);
    string identifyDevice(int);

    // Ask-function
    int readMessage(char*, int, int);
	  int acceptConnection();
    bool readFile(string);

private:
    int server_socket;
    socklen_t client_address_length;
    struct sockaddr_in server_address, client_address;
};
#endif //SOCKET_1_2_SOCKET_SERVER_H
