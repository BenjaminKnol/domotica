//
// Created by nhutt on 18/01/2021.
//

#ifndef SOCKETS_TABLE_LAMP_H
#define SOCKETS_TABLE_LAMP_H
class Table_lamp {
    public:
        void toggle_led();
        int status_update();
        Table_lamp(bool a_led, double a_motion_sensor) {
            led = a_led;
            motion_sensor = a_force_sensor;
        }

    private:
        bool led;
        double motion_sensor;
};
#endif //SOCKETS_TABLE_LAMP_H
