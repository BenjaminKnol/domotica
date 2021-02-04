//
// Created by Asus on 20-1-2021.
//

#include "Door.h"

//TODO als de knop op de interface wordt ingedrukt, toggle de deur

void Door::handle(string buffer) {

    toggleDoor();
}

void Door::toggleDoor() {
    if(getStatus()){
        setStatus(0);
        strcpy(toPHP, "Close door");
        send(getSocketId(), "0\n", 2, 0);
        cout << "Close door" << endl;
    }else {
        setStatus(1);
        strcpy(toPHP, "Door has opened");
        send(getSocketId(), "1\n", 2, 0);
        cout << "Door has opened" << endl;
    }
}
