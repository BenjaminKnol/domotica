/*
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *
 */
#ifndef CLASSSTRUCTURE_COMPONENT_H
#define CLASSSTRUCTURE_COMPONENT_H

#include <string>
#include <ctime>
#include <iostream>
#include "../../Socket.h"

using namespace std;

class Component {

private:
    string unique_id;
    string name;
    string description;
    int socketId;
    int status;
    time_t timeOfDay = time(0);

public:
    string getId() const;
    void setId(string);
    const string &getName() const;
    void setName(const string &name);
    const string &getDescription() const;
    int getStatus() const;
    time_t getTimeOfDay();
    char *getTimeOfDayUTC(time_t timeOfDay);
    void setDescription(const string &description);
    void setStatus(int status);
    void setSocketId(int);
    int getSocketId();
    void cacheStatus();
    virtual void handle(string); // Handles incoming messages

};


#endif //CLASSSTRUCTURE_COMPONENT_H
