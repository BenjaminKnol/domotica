//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_WALL_H
#define CLASSSTRUCTURE_WALL_H


#include "Base/Component.h"
#include "Base/WithLed.h"

class Wall : public Component, public WithLed {

private:
    int setDimmer();          //dims the LEDstrip
    int DarkenWindow();    //sets amount of darkening for the window

public:
    Wall(const string &name, const string &description) {
        new WithLed();
        Wall::setName(name);
        Wall::setDescription(description);
    }
};


#endif //CLASSSTRUCTURE_WALL_H
