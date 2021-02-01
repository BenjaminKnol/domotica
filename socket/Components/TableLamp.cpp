//
// Created by Asus on 20-1-2021.
//

#include "TableLamp.h"
#define WEBSERVER_ID 100

void TableLamp::detectMotion() {
    if (TableLamp::motionSensorStatus) {
        TableLamp::toggleLedStatus();
    } else {
        return;
    }
}
// int TableLamp::cacheStatus(int serverId, int status, int socket) {
//     Socket_server functionalCaller;
//     if (serverId == WEBSERVER_ID) {
//         cachedStatus = status;
//         return 2; //returns '2' if state is cached (bc 0 and 1 could be confused with states)
//     } else {
//         functionalCaller.send_message(to_string(cachedStatus), socket);
//         return cachedStatus; // returns status if there is one cached
//     }
// }
