//
// Created by nhutt on 18/01/2021.
//

#ifndef SOCKETS_FRIDGE_H
#define SOCKETS_FRIDGE_H


class Fridge {
    public:
        void toggle_led();
        int status_update();
        Fridge(bool a_cooling_element, bool door_switch, double a_temperature_sensor {
            temperature_sensor = a_temperature_sensor;
            cooling_element = a_cooling_element;
            door_switch = a_door_switch;
        }

    private:
        bool cooling_element;
        bool door_switch;
        double temperature_sensor;
};


#endif //SOCKETS_FRIDGE_H
