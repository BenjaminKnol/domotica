//
// Created by Asus on 20-1-2021.
//

#include "WithForceSensor.h"

double WithForceSensor::getForce() const {
    return force;
}

void WithForceSensor::setForce(double force) {
    WithForceSensor::force = force;
}
