#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Socket header files
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define NETWORK_QUEUE 5

int main() {
	
	// variables
	int server_socket;
	struct sockaddr_in server_address;
	int new_connection;
	int addrlen = sizeof(server_address); // adres lengte in variabele
	
	// open a file to serve
	FILE *html_data; //File pointer, to hold the data
	html_data = fopen("index.html", "r");
	
	char response_data[1024]; //Store HTML file 
	fgets(response_data, 1024, html_data);
	
	char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
	strcat(http_header, response_data);
	
	
	//Create a server socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0); //IPv4 and TCP connection
	
	//Define server address, where the server is 
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;	//Any server_address will be assigned on the local machine
	
	//Bind
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	
	//Listen
	listen(server_socket, NETWORK_QUEUE);
	
	while(1) {
		//Accept, holding a connection from a client
		new_connection = accept(server_socket, (struct sockaddr*) &server_address, (socklen_t*) &addrlen);
		
		send(new_connection, http_header, sizeof(http_header), 0); 	//Send/Recv
		printf("%s\n", "Bericht is verstuurd naar client!");
		//close(new_connection);
	}	
	
	return 0;
}