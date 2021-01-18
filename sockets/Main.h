//
// Created by nhutt on 18/01/2021.
//

#ifndef SOCKETS_BED_H
#define SOCKETS_BED_H
class Main {
public:
    int chair(char type, int status);
    int door(char type, int status);
    int bed(char type, int status);
    int wall(char type, int status, char time_of_day);
    int column();
    int table_lamp(char type, int status, char time_of_day);
    int fridge(int status); 

private:

};
#endif //SOCKETS_BED_H
