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
#include "Json_conversion.h"


#define LENGTH 256

using namespace std;
void get_json(string message) {
  Json::Value json; // JSON document
  Json::Reader reader; // Create read object
  reader.parse(message, json, false);
  Json::Value id = json.get("type", Json::nullValue).asString();      // Get 'id' as a string
  Json::Value status = json.get("status", Json::nullValue).asInt();   // Get 'status' as an int
  cout << "This should be the ID: " << id << endl;
  cout << "This should be the status: " << status << endl;
}
int main() {
    Socket_server socket;
    Json_conversion json_conv;
    socket.create_socket();     // 1. Create Socket 2. Bind Socket. 3. Listen to Socket

    while (true) {
        string message;
        string* message_ptr = &message;
        int child_socket = socket.accept_connection(); // 4. Accept Socket Connection
		if (child_socket > 0) {
      std::thread thread_socket(Socket_threading(), message_ptr, LENGTH, child_socket);
      thread_socket.join();
      Json_conversion::deserializer(&json_conv, message);
      cout << "WERKT DIT? " << json_conv.get_id() << endl;
      // get_json(message);

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
