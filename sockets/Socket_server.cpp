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
#include "Socket_server.h"

#define NETWORK_QUEUE 8

Socket_server::Socket_server() {
}

// 1. Create a socket with the socket() system call.
void Socket_server::create_socket() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("Could not create socket\n");
    } else {
        printf("Socket is created!\n");
    }

    // Define the server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;    // Any address
    server_address.sin_port = htons(port);

    /* 2. Bind the socket to an address using the bind() system call.
       For a server socket on the Internet, and address consists of a port number on the host machine. */
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    listen_to_client();
}

// 3. Listen for connections with the listen() system call.
void Socket_server::listen_to_client() {
    listen(server_socket, NETWORK_QUEUE);
}

/* 4. Accept a connection with the accept() system call.
   This call typically blocks untill a client connects with the server. */
int Socket_server::accept_connection() {
    printf("Waiting for incoming connection...\n");
    client_address_length = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_address_length);
    if (client_socket == -1) {
        printf("Error\n");
    } else {
        printf("Connection has been established\n");
    }
    return client_socket;
}

// Send data
void Socket_server::send_message(string msg, int child_socket) {
    const char *send_buffer = msg.c_str();
    int len = (int) strlen(send_buffer);
    int status = send(child_socket, send_buffer, len, 0);

    if (status < 0) {
        printf("Send error\n");
    }
}
