//
// Created by Asus on 20-1-2021.
//

#include "Fridge.h"

void Fridge::handle(string buffer) {
    if (buffer.find("door closed") < 255) {
        setStatus(0);
        toPHP = "door closed";
    } else if (buffer.find("forgot to close door")) {
        setStatus(1);
        toPHP = "forgot to close door";
    } else {
        float currentTemp = stof(buffer);
        setTemperature(currentTemp);
        if (currentTemp > 4.0) {
            send(getSocketId(), "1\n", 2, 0);
            CoolElement::setStatus(1);
        } else {
            send(getSocketId(), "0\n", 2, 0);
            CoolElement::setStatus(0);
        }
    }
}

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
