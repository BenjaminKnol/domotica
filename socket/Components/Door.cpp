//
// Created by Asus on 20-1-2021.
//

#include "Door.h"

//TODO als de knop op de interface wordt ingedrukt, toggle de deur

void Door::handle(string buffer) {
    toggleDoor();
}

int Door::toggleDoor() {
    if(getStatus()){
        send(getSocketId(), "0\n", 2, 0);
    }else {
        send(getSocketId(), "1\n", 2, 0)
    }
}