/*
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 */

#include "Socket_server.h"
#include "Socket_threading.h"
#include "Json_conversion.h"

#define MESSAGE_LENGTH 256

int main() {
    Socket_server socket;
    Json_conversion import_export_json;
    socket.create_socket();     // 1. Create Socket 2. Bind Socket. 3. Listen to Socket

    while (true) {
      string receive_message, send_message;
      string* message_ptr = &receive_message;
      int child_socket = socket.accept_connection(); // 4. Accept Socket Connection
		if (child_socket > 0) {
      std::thread thread_socket(Socket_threading(), message_ptr, MESSAGE_LENGTH, child_socket);
      import_export_json.deserializer(receive_message); // Get data from JSON-object.
      import_export_json.serializer(send_message);  // Parse data to JSON-object
      socket.send_message(send_message);
      thread_socket.join();

		} else {
            continue; 
    }
    // switch case on type where u can call OBJECT.handle(val)
    }
    return 0;
}

// ARCHIVED (test) functions or variables:
// import_export_json.set_id("Schemerlamp"); // Assigning
// import_export_json.set_status(1);
// cout << "MAIN 1: " << json_conv.get_id() << endl;
// cout << "MAIN 2: " << json_conv.get_status() << endl;
