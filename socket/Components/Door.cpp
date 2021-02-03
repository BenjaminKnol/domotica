//
// Created by Asus on 20-1-2021.
//

#include "Door.h"

//TODO als de knop op de interface wordt ingedrukt, toggle de deur

void Door::handle(string buffer) {
    int len = (int)strlen(buffer);
    send(socketId, buffer, len, 0));
}
