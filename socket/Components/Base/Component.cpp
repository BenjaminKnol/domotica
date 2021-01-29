#define WEBSERVER_ID 100

#include "Component.h"

int Component::getId() const {
    return id;
}

void Component::setId(int id) {
    Component::id = id;
}

const string &Component::getName() const {
    return name;
}

void Component::setName(const string &name) {
    Component::name = name;
}

const string &Component::getDescription() const {
    return description;
}

void Component::setDescription(const string &description) {
    Component::description = description;
}

int Component::getStatus() const {
    return status;
}

void Component::setStatus(int status) {
    Component::status = status;
}

time_t Component::getTimeOfDay() {
    return time(0);
}

char *Component::getTimeOfDayUTC(time_t timeOfDay) {
    char *dt;
    tm *gmtm = gmtime(&timeOfDay);
    dt = asctime(gmtm);
    return dt;

}
bool Component::check_device(int client_socket, char unique_id) {
  Socket_server s;
  switch(unique_id) {
    // case 'b': // Bed
    //     break;
    // case 'c':  // Chair
    //     break;
    // case 'f': // Frigde
    //     break;
    case 'w': // Wall
        break;
    // case 't': // Table Lamp
    //     break;
    // case 'd': // Door
    //     break;
    // case 'z': // Column (dutch=Zuil)
    //     break;
    // case 'p': // Web(P)age
    //     break;
    default:
        cout << "Could not match the appropriate ID.\n"; return true;
        break;
  }
  return false;
}

// int Component::cacheStatus(int serverId, int status, int child_socket) {
//   Socket_server socket;
//     if (serverId == WEBSERVER_ID){
//         cachedStatus = status;
//         cout << status << endl;
//         return 2; //returns '2' if state is cached (bc 0 and 1 could be confused with states)
//     }
//     else{
//         cout << status << endl;
//         socket.send_message(to_string(cachedStatus), child_socket);
//         return cachedStatus; // returns status if there is one cached
//     }
// }
