//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_FRIDGE_H
#define CLASSSTRUCTURE_FRIDGE_H


#include "Base/Component.h"

class Fridge : public Component {
    class CoolElement {
    public:
        int status;

        int getStatus() const;

        void setStatus(int status);

    };

private:
    float temperature{};
public:
    Fridge(int id, const string &name, const string &description) {
        new Fridge::CoolElement();
        Fridge::setId(id);
        Fridge::setName(name);
        Fridge::setDescription(description);
    };

public:
    float getTemperature() const;

    void setTemperature(float temperature);

public:

};


#endif //CLASSSTRUCTURE_FRIDGE_H
