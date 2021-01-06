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

using namespace std;
/*
	> Steps for establishing a socket on the server side are as follows:
	1. Create a socket with the socket() system call.
	2. Bind the socket to an address using the bind() system call.
		For a server socket on the Internet, and address consists of a port number on the host machine.
	3. Listen for connections with the listen() system call.
	4. Accept a connection with the accept() system call.
		This call typically blocks until a client connects with the server.
	5. Send and receive data.
*/
class Socket_server {
public:
    Socket_server(); // Default constructor

    // Do-function
    void create_socket();
    void listen_to_client();
    void send_message(string msg);

    // Ask-function
    int read_message(string &buf, int length);
    int accept_connection();

private:
    int server_socket;
    int client_socket;
    socklen_t client_address_length;
    struct sockaddr_in server_address, client_address;
    int port = 9002;
};
#endif //SOCKET_1_2_SOCKET_SERVER_H
