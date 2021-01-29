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
#include "Json_conversion.h"

int main() {
    Socket_server socket;
    socket.create_socket();     // 1. Create Socket 2. Bind Socket. 3. Listen to Socket
    Json_conversion import_export_json;

    while (true) {
        string receive_message, send_message;
        int child_socket = socket.accept_connection(); // 4. Accept Socket Connection
        if (child_socket > 0)
          if (!(receive_message.empty())) {
            import_export_json.deserializer(receive_message); // Get data from JSON-object.
          }
        } else {
            continue;
        }
    }
    return 0;
}

// ARCHIVED (test) functions or variables:
// import_export_json.set_id("Schemerlamp"); // Assigning
// import_export_json.set_status(1);
// cout << "MAIN 1: " << json_conv.get_id() << endl;
// cout << "MAIN 2: " << json_conv.get_status() << endl;
// socket.send_message("Hello from RPi");
