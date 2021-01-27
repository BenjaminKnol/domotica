//
// Created by Asus on 20-1-2021.
//

#include "TableLamp.h"


void TableLamp::detectMotion() {
    if (TableLamp::motionSensorStatus) {
        TableLamp::toggleLedStatus();
    } else {
        return;
    }
}
