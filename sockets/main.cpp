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
 * Version: 1.1 ---> Server socket code is re-written to Object Orientated.
 *
 * Used sources: https://bit.ly/3h4MdW3  ---> Socket explanation.
 */

#include "Socket_server.h"

using namespace std;

int main() {
    char send_message[256] = "Hello from RPi4";
    string read_message;
    Socket_server socket; // Creating an object

    socket.create_socket();     // 1. Create a socket
    socket.listen_to_client();  // 3. Listen to incoming connection from clients.

    while (true) {
        int amount_of_clients = socket.accept_connection();
        if (amount_of_clients < 1) {
            continue;
        } else {
            break;
        }
    }

    socket.send_message(send_message);  // Send data to Wemos
    socket.read_message(read_message, 256); // Read data from Wemos

//    cout << "Message from client: " << read_message << endl;    // --> DEBUG only

    return 0;
}
