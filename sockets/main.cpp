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
 *               https://www.geeksforgeeks.org/multithreading-in-cpp/            ---> Callable class
 */

#include "Socket_server.h"
#include "Socket_threading.h"

#define LENGTH 256

using namespace std;

int main() {
    Socket_server socket;
    socket.create_socket();     // 1. Create Socket 2. Bind Socket. 3. Listen to Socket

    while (true) {
        string message;
        int child_socket = socket.accept_connection(); // 4. Accept Socket Connection
		if (child_socket > 0) {
      std::thread thread_socket(Socket_threading(), message, LENGTH, child_socket);
      thread_socket.join();
      printf("%s\n", message);
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
