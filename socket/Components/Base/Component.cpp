/*
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *
 */
#include "Component.h"

string Component::getId() const {
    return unique_id;
}
void Component::setId(string id) {
    unique_id = id;
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
void Component::cacheStatus() {
    char buffer[256];
    send(socketId, "RTR", 256, 0); // Send request for unique id to WEMOS
    recv(socketId, buffer, 256, 0);
    handle(string(buffer));

}
void Component::handle(string buffer) {}

void Component::setSocketId(int socket) {
    socketId = socket;
}
int Component::getSocketId() {
    return socketId;
}
