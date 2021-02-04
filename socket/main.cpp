/*
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 */

#include "Socket.h"
#include "Json_conversion.h"
#include <algorithm>
#include <cctype>

// #include "Components/Base/Component.h"
// #include "Components/Chair.h"
// #include "Components/Bed.h"
// #include "Components/Column.h"
#include "Components/Door.h"
// #include "Components/Fridge.h"
// #include "Components/TableLamp.h"
#include "Components/Wall.h"

int main() {
    Socket socket;
    socket.createSocket();     // 1. Create Socket 2. Bind Socket. 3. Listen to Socket
    Json_conversion importExportJson;

    // Start Component objects
    // auto *bed = new Bed("Bed", "pretty soft bed");
    // auto *chair = new Chair("Chair", "nice vibratin chair");
    // auto *fridge = new Fridge("Fridge", "cool fridge");
    auto *wall = new Wall("Wall", "rocksollid");
    // auto *tableLamp = new TableLamp("Table Lamp", "Nice and bright");
    auto *door = new Door("Door", "KaSLAMo");
    // auto *column = new Column("Column", "it's getting dark in here");
    // End Component objects
    vector < Component * > components{wall, door};
    // vector<Component*> components {bed, chair, column, fridge, wall, tableLamp, door};

    int counter = 0, allDevicesSet = 0;
    while (!allDevicesSet) {
        int childSocket = socket.acceptConnection(); // 4. Accept Socket Connection
        if (childSocket > 0) {
            string uniqueId = socket.identifyDevice(childSocket);
            for (int i = 0; i < components.size(); i++) {
                string componentId = components[i]->getName();
                transform(componentId.begin(), componentId.end(), componentId.begin(),
                          [](unsigned char c) { return tolower(c); });
//                cout << "currentId:" << (int) (components[i]->getId() == "") << endl;
//                cout << "uniqueId.find(componentId):" << uniqueId.find(componentId) << endl;
                if (uniqueId.find(componentId) < 255 && components[i]->getId() == "") {
                    cout << "uniqueId: " << uniqueId << endl;
                    components[i]->setId(uniqueId);
                    counter++;
                    close(childSocket);
                    childSocket = 0;
                    if (counter >= components.size()) {
                        allDevicesSet = 1;
                    }
                }
            }
        } else {
            continue;
        }
    }
    cout << "end of loop 1" << endl;
    while (true) {
        string receiveMessage, sendMessage;
        int childSocket = socket.acceptConnection(); // 4. Accept Socket Connection
        if (childSocket > 0) {
            string tempId = socket.identifyDevice(childSocket);
            for (int i = 0; i < components.size(); i++) {
                if (tempId.find("p") >= 0) {
                    socket.readMessage(receiveMessage, 256, childSocket);
                    importExportJson.deserializer(receiveMessage);
                    cout << importExportJson.getId() << endl;
                    continue;
                }
                if (tempId.find(components[i]->getId()) >= 0) {
                    components[i]->setSocketId(childSocket);
                    components[i]->cacheStatus();
                    continue;
                }
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
// cout << "MAIN: " << socket.get_id() << endl;

// string id = socket.identify_device(client_socket);
