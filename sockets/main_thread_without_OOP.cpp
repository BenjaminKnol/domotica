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
 * Version: 1.0 ---> Set TCP/IP connection between WEMOS en RPi4
 * Version: 1.1 ---> Server socket code is re-written to be Object Orientated.
 *
 * Used sources: https://www.bogotobogo.com/cplusplus/sockets_server_client.php  ---> Socket explanation.
 */

#include "Socket_server.h"

char client_message[256];
char buffer[256];

using namespace std;
void *reading_message(void * arg) {

    int new_socket = *((int *)arg);
	recv(new_socket, client_message, 256, 0);
	
	
	cout<<"Passed String = "<<client_message<< endl;
	pthread_exit(NULL);
	
	return NULL;
}
int main() {
	string read_message;
	
    Socket_server socket; 		// Creating an object
    socket.create_socket();     // 1. Create a socket
    socket.listen_to_client();  // 3. Listen to incoming connection from clients
	
    while (true) {
        int amount_of_clients = socket.accept_connection();
		pthread_t threads;
		if (amount_of_clients > 0) {
			pthread_create(&threads, NULL, reading_message, &amount_of_clients);
			pthread_join(threads, NULL);
			// thread threads(&Socket_server::read_message, &socket);
			// threads.join();
		}else {
            continue;
        }	
			// split message into type and val

			// switch case on type where u can call OBJECT.handle(val) 
		
    }

    return 0;
}

// ARCHIVED functions or variables:
//    char send_message[256] = "Hello from RPi4";
//    socket.send_message(send_message);  // Send data to Wemos