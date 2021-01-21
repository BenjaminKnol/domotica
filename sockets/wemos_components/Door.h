//
// Created by nhutt on 18/01/2021.
//

#ifndef SOCKETS_DOOR_H
#define SOCKETS_DOOR_H


class Door {
    public:
        void toggle_led();
        int door(int status);
        Door(bool a_led, bool door_switch, double a_servo) {
            led = a_led;
            servo = a_servo;
        }

    private:
        bool led;
        bool door_switch;
        double servo;
};


#endif //SOCKETS_DOOR_H
