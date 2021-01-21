//
// Created by nhutt on 18/01/2021.
//

#ifndef SOCKETS_CHAIR_H
#define SOCKETS_CHAIR_H


class Chair {
    public:
        void vibrating();
        int status_update();
        Chair(bool a_vibrator, double a_force_sensor) {
            vibrator = a_vibrator;
            force_sensor = a_force_sensor;
        }

    private:
        bool vibrator;
        double force_sensor;
};


#endif //SOCKETS_CHAIR_H
