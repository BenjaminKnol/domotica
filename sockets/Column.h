//
// Created by nhutt on 18/01/2021.
//

#ifndef SOCKETS_COLUMN_H
#define SOCKETS_COLUMN_H


class Column {
    public:
        int status_update();
        int buzzing(int status);
        Column(bool a_smoke_detector, bool smoke_detector_switch, bool buzzer) {
            smoke_detector_switch= a_smoke_detector_switch;
            buzzer = a_buzzer;
            smoke_detector = a_smoke_detector;
        }

    private:
        bool smoke_detector_switch;
        bool buzzer;
        bool smoke_detector;
};


#endif //SOCKETS_COLUMN_H
