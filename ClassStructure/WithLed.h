//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_WITHLED_H
#define CLASSSTRUCTURE_WITHLED_H


class WithLed {
private:
    int ledStatus;
public:
    int getLedStatus() const;

    void setLedStatus(int ledStatus);
};


#endif //CLASSSTRUCTURE_WITHLED_H
