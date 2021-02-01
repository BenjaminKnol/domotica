//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_BED_H
#define CLASSSTRUCTURE_BED_H


#include "Base/Component.h"
#include "Base/WithLed.h"
#include "Base/WithForceSensor.h"

class Bed : public Component, public WithLed, public WithForceSensor {

public:

    Bed(const string &name, const string &description) {
        new WithLed();
        new WithForceSensor();
        Bed::setName(name);
        Bed::setDescription(description);
    }

};


#endif //CLASSSTRUCTURE_BED_H
