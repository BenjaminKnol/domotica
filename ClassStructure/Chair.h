//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_CHAIR_H
#define CLASSSTRUCTURE_CHAIR_H


#include "WithForceSensor.h"
#include "Component.h"

class Chair : public Component, public WithForceSensor {

private:
    int vibratorStatus;

public:
    Chair(int id, const string& name, const string& description){
    new WithForceSensor();
    Chair::setId(id);
    Chair::setName(name);
    Chair::setDescription(description);

    }

    int getVibratorStatus() const;

    void setVibratorStatus(int vibratorStatus);
};


#endif //CLASSSTRUCTURE_CHAIR_H
