#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define NETWORK_QUEUE 2

int main() {
		// Variabele declaration
		int client_socket;
		struct sockaddr_in server_address;
		int new_connection;
		char server_antwoord[256];
		
		//Aanmaken socket
		client_socket = socket(AF_INET, SOCK_STREAM, 0); //IPv4 and TCP connection
		
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(PORT);
		server_address.sin_addr.s_addr = INADDR_ANY;	//Any server_address will be assigned on the local machine
		
		// Verbindt met server
		new_connection = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));
		
		// Controleer verbinding of er geen fouten zijn.
		if (new_connection == -1) {
			printf("%s\n", "Er is een fout in het maken van een verbinding met de server!");
		}
		
		// Ontvang gegevens van de server
		recv(client_socket, &server_antwoord, sizeof(server_antwoord), 0);
		
		// print out the server's response 
		printf("De server antwoord met: %s\n", server_antwoord);
	
		//Closing the server socket
		//close(client_socket);
		return 0;
}