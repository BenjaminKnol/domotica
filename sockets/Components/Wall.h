//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_WALL_H
#define CLASSSTRUCTURE_WALL_H


#include "Component.h"
#include "WithLed.h"

class Wall : public Component, public WithLed{

private:
    Wall::setDimmer();          //dims the LEDstrip
    Wall::DarkenWindow();    //sets amount of darkening for the window
};

public:
    Wall(int id, const string& name, const string& description){
        new WithLed();
        Wall::setId(id);
        Wall::setName(name);
        Wall::setDescription(description);
    }






#endif //CLASSSTRUCTURE_WALL_H