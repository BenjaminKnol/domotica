//
// Created by Asus on 20-1-2021.
//

#include "WithLed.h"

int WithLed::getLedStatus() const {
    return ledStatus;
}

void WithLed::setLedStatus(int status) {
    WithLed::ledStatus == false ? WithLed::ledStatus = true : WithLed::ledStatus = false;
}
