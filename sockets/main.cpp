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

#include "Components/Chair.h"
#include "Components/Bed.h"
#include "Components/Column.h"
#include "Components/Door.h"
#include "Components/Fridge.h"
#include "Components/TableLamp.h"
#include "Components/Wall.h"

#define MESSAGE_LENGTH 256
Json_conversion import_export_json;

// Start Component objects
auto *bed_obj = new Bed(1, "Bed", "pretty soft bed");
auto *chair_obj = new Chair(2, "Chair", "nice vibratin chair");
auto *fridge_obj = new Fridge(3, "Fridge", "cool fridge");
auto *wall_obj = new Wall(4, "Wall", "rocksollid");
auto *table_lamp_obj = new TableLamp(5, "Table Lamp", "Nice and bright");
auto *door_obj = new Door(6, "Door", "KaSLAMo");
//auto *column_obj = new Column(7, "Column", "it's getting dark in here");
// End Component objects

void menu(int child_socket) {
    switch (import_export_json.get_id()) {
        case 1: // bed led
            bed_obj->cacheStatus(import_export_json.get_unique_id(), import_export_json.get_status(), child_socket);
            break;
        case 2: // chair
            chair_obj->cacheStatus(import_export_json.get_unique_id(), import_export_json.get_status(), child_socket);
            break;
        case 3: // fridge
            fridge_obj->cacheStatus(import_export_json.get_unique_id(), import_export_json.get_status(), child_socket);
            break;
        case 4: // wall
            wall_obj->cacheStatus(import_export_json.get_unique_id(), import_export_json.get_status(), child_socket);
            break;
        case 5: // table lamp
            table_lamp_obj->cacheStatus(import_export_json.get_unique_id(), import_export_json.get_status(), child_socket);
            break;
        case 6: // door
            door_obj->cacheStatus(import_export_json.get_unique_id(), import_export_json.get_status(), child_socket);
            break;
        case 7: // column
            // column_obj->cacheStatus(import_export_json.get_unique_id(), import_export_json.get_status(), child_socket);
            break;
        default:
            cout << "Could not match the appropriate ID.\n";
            // error code here
            break;
    }
}

int main() {
    Socket_server socket;
    socket.create_socket();     // 1. Create Socket 2. Bind Socket. 3. Listen to Socket

    while (true) {
        string receive_message, send_message;
        string *message_ptr = &receive_message;
        int child_socket = socket.accept_connection(); // 4. Accept Socket Connection
        if (child_socket > 0) {
            std::thread thread_socket(Socket_threading(), message_ptr, MESSAGE_LENGTH, child_socket);
            thread_socket.join();
            if (!(receive_message.empty())) {
                import_export_json.deserializer(receive_message); // Get data from JSON-object.
                menu(child_socket);
            }
        } else {
            continue;
        }
    }
    return 0;
}

// ARCHIVED (test) functions or variables:
// socket.send_message(send_message);  // Send data to Wemos
// import_export_json.set_id("Schemerlamp"); // Assigning
// import_export_json.set_status(1);
// cout << "MAIN 1: " << json_conv.get_id() << endl;
// cout << "MAIN 2: " << json_conv.get_status() << endl;
