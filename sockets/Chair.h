//
// Created by nhutt on 18/01/2021.
//

#ifndef SOCKETS_CHAIR_H
#define SOCKETS_CHAIR_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#include "Socket_server.h"

class Chair {
    public:
        Chair(); // Default constructor
        void chair(int unique_id, int status, int sock); // starting point for main
        void vibrating();
        int status_update();
        // Chair(bool a_vibrator, double a_force_sensor) {
        //     vibrator = a_vibrator;
        //     force_sensor = a_force_sensor;
        // }

    private:
        bool vibrator;
        double force_sensor;

        bool rts_vibrator;
        double rts_force_sensor;
};


#endif //SOCKETS_CHAIR_H
