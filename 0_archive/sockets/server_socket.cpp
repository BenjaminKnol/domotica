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
 * Versie: 1.0 ---> Set TCP/IP connection between WEMOS en RPi4
 *    
 * Bronnen: https://www.linuxhowtos.org/C_C++/socket.htm?print=208
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9002
#define NETWORK_QUEUE 5 //How many connections can be waiting while the process is handling a particular connection.

/*
	> Steps for establishing a socket on the server side are as follows:
	1. Create a socket with the socket() system call.
	2. Bind the socket to an address using the bind() system call. 
		For a server socket on the Internet, and address consists of a port number on the host machine.
	3. Listen for connections with the listen() system call. 
	4. Accept a connection with the accept() system call.
		This call typically blocks untill a client connects with the server.
	5. Send and receive data.
*/
	
int main() {
	// Variable declerations 
	int server_socket;
	int client_socket;
	socklen_t client_address_length;
	struct sockaddr_in server_address, client_address;
	
	char send_buffer[256] = "You have reached the server!";
	char receive_buffer[256];
	
	
	//1. Create a socket with the socket() system call.
	server_socket = socket(AF_INET, SOCK_STREAM, 0); 
	if (server_socket == -1) {
		printf("Could not create socket\n");
	} else {
		printf("Socket is created!\n");
	}
	
	
	// Define the server address structure 
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;	// Any address 
	server_address.sin_port = htons(PORT);
	
	
	/*2. Bind the socket to an address using the bind() system call. 
		For a server socket on the Internet, and address consists of a port number on the host machine.*/
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	
	//3. Listen for connections with the listen() system call. 
	listen(server_socket, NETWORK_QUEUE);
	
	
	/*4. Accept a connection with the accept() system call.
		This call typically blocks untill a client connects with the server.*/
	printf("Waiting for incoming connection...\n");
	client_address_length = sizeof(client_address);
	client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_address_length);
	
	//5. Send and receive data.
		// Receive data from client
		bzero(receive_buffer, 256);	// The function bzero() erases the data in the n bytes of the memory.
		int n = read(client_socket,receive_buffer, 255);
		if (n < 0) {
			printf("Error reading from socket\n");
		} else {
			printf("Message: %s\n", receive_buffer);
		}
		
		// Send data
		send(client_socket, send_buffer, sizeof(send_buffer), 0);
	
	close(server_socket); // Closing server socket.
	
	return 0;
}
