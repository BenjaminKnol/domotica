//
// Created by nhutt on 18/01/2021.
//

#ifndef SOCKETS_WALL_H
#define SOCKETS_WALL_H


class Wall {
public:
    void darken();
    void dimming();
    Wall(bool a_led_strip, int a_window, double a_ldr, double a_dimmer) {
        led_strip = a_led_strip;
        window = a_window;
        ldr = a_ldr;
        dimmer = a_dimmer;
    }

private:
    bool led_strip;
    int window;
    double ldr;
    double dimmer
};


#endif //SOCKETS_WALL_H
