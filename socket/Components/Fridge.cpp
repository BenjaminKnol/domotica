//
// Created by Asus on 20-1-2021.
//

#include "Fridge.h"

int Fridge::CoolElement::getStatus() const {
    return status;
}

void Fridge::CoolElement::setStatus(int status) {
    CoolElement::status = status;
}

float Fridge::getTemperature() const {
    return temperature;
}

void Fridge::setTemperature(float temperature) {
    Fridge::temperature = temperature;
}

