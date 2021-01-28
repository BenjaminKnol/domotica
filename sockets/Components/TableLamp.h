//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_TABLELAMP_H
#define CLASSSTRUCTURE_TABLELAMP_H


#include "Base/Component.h"
#include "Base/WithLed.h"
#include "../Socket_server.h"

class TableLamp : public Component, public WithLed {
private:
    int motionSensorStatus = false;
public:
    TableLamp(int id, const string &name, const string &description) {
        new WithLed();
        TableLamp::setId(id);
        TableLamp::setName(name);
        TableLamp::setName(description);
    }
    virtual int cacheStatus(int serverId, int status, int socket) override;

    void detectMotion();
};


#endif //CLASSSTRUCTURE_TABLELAMP_H
