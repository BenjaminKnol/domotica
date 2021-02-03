//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_DOOR_H
#define CLASSSTRUCTURE_DOOR_H


#include "Base/Component.h"
#include "Base/WithLed.h"

class Door : public Component, public WithLed {

private:
    void toggleDoor();

public:
    Door(const string &name, const string &description) {
        new WithLed();
        Door::setName(name);
        Door::setDescription(description);
    }
    virtual ~Door(){};
    void handle(string);
};


#endif //CLASSSTRUCTURE_DOOR_H
