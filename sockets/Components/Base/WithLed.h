//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_WITHLED_H
#define CLASSSTRUCTURE_WITHLED_H


class WithLed {
private:
    int ledStatus = false;
public:
    int getLedStatus() const;

    void toggleLedStatus();
};


#endif //CLASSSTRUCTURE_WITHLED_H
