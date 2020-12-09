/* ----------------------------------------------------------------------------------*
* Author          			Name				Lastname		Studentnumber 	     *
*					        Noureddine			Ait Jaa			15018628             *
*																					 *
*																					 *
* Goal application:			Server socket is trying to listen to incoming 			 *
*							connection from clients.								 *
*																					 *
*																					 *
* -----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define NETWORK_QUEUE 5


int main() {
	
	// Variabele declaration
	char buffer[256] = "Er is een verbinding!";

	int server_socket;
	struct sockaddr_in server_address;
	int new_connection;
	int addrlen = sizeof(server_address); // adres lengte in variabele
	
	//Create a server socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0); //IPv4 and TCP connection
	
	//Define server server_address 
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;	//Any server_address will be assigned on the local machine
	
	
	//Bind
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	
	//Listen
	listen(server_socket, NETWORK_QUEUE);
	
	//Accept, holding a connection from a client
	new_connection = accept(server_socket, (struct sockaddr*) &server_address, (socklen_t*) &addrlen);
	
	
	//Send/Recv
	send(new_connection, buffer, sizeof(buffer), 0);
	printf("%s\n", "Bericht is verstuurd naar client!");
	
	
	//Closing the server socket
	//close(server_socket);
	
	return 0;
}