//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_DOOR_H
#define CLASSSTRUCTURE_DOOR_H


#include "Base/Component.h"
#include "Base/WithLed.h"

class Door : public Component, public WithLed {

private:
    int toggleDoor();

public:
    Door(int id, const string &name, const string &description) {
        WithLed led = new Withled();
        Door::setId(id);
        Door::setName(name);
        Door::setDescription(description);
    }
};


#endif //CLASSSTRUCTURE_DOOR_H
