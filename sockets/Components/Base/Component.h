//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_COMPONENT_H
#define CLASSSTRUCTURE_COMPONENT_H

#include <string>
#include <ctime>

using namespace std;

class Component {

private:
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

    void cacheStatus(int serverId, int status);
};


#endif //CLASSSTRUCTURE_COMPONENT_H
