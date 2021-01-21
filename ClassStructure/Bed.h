//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_BED_H
#define CLASSSTRUCTURE_BED_H


#include "Component.h"
#include "WithLed.h"
#include "WithForceSensor.h"

class Bed : public Component, public WithLed, public WithForceSensor{

public:

    Bed(int id, const string& name, const string& description){
        new WithLed();
        new WithForceSensor();
        Bed::setId(id);
        Bed::setName(name);
        Bed::setDescription(description);
    }

};



#endif //CLASSSTRUCTURE_BED_H
