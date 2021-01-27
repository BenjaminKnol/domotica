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
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

using namespace std;

class Socket_server {
public:
    Socket_server(); // Default constructor

    // Do-function
    void create_socket();

    void listen_to_client();

    void send_message(string msg, int sock);

    // Ask-function
    int accept_connection();

private:
    int server_socket;
    int client_socket;
    socklen_t client_address_length;
    struct sockaddr_in server_address, client_address;
    int port = 9002;
};

#endif //SOCKET_1_2_SOCKET_SERVER_H
