#ifndef CLASSSTRUCTURE_COMPONENT_H
#define CLASSSTRUCTURE_COMPONENT_H

#include <string>
#include <ctime>
#include <iostream>

#include "../../Socket_server.h"

using namespace std;

class Component {

protected:
    int id;
    string name;
    string description;
    int status;
    time_t timeOfDay = time(0);
    int cachedStatus;

public:
    int getId() const;
    void setId(int id);
    const string &getName() const;
    void setName(const string &name);
    const string &getDescription() const;
    int getStatus() const;
    time_t getTimeOfDay();
    char *getTimeOfDayUTC(time_t timeOfDay);
    void setDescription(const string &description);
    void setStatus(int status);
    bool check_device(int client_socket, char client_id);

    // void deserializer(string &message);
    // virtual int cacheStatus(int serverId, int status, int child_socket);
};


#endif //CLASSSTRUCTURE_COMPONENT_H
