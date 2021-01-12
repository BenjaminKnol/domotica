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
#include "findLocalIp.h"

using namespace std;

int main() {
    findLocalIp.findLocalIp();
    string read_message;
    Socket_server socket; // Creating an object

    socket.create_socket();     // 1. Create a socket
    socket.listen_to_client();  // 3. Listen to incoming connection from clients.

    while (true) {
        int amount_of_clients = socket.accept_connection();
        if (amount_of_clients > 0) {

            socket.read_message(read_message, 256); // Read data from Wemos
			cout << "Message from client: " << read_message << endl;    // --> DEBUG only

			//split message into type and val

			//switch case on type where u can call OBJECT.handle(val)
        } else {
            continue;
        }
    }

    return 0;
}

// ARCHIVED functions or variables:
//    char send_message[256] = "Hello from RPi4";
//    socket.send_message(send_message);  // Send data to Wemos
