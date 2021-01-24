//
// Created by Asus on 20-1-2021.
//

#include "Component.h"

int Component::getId() const {
    return id;
}

void Component::setId(int id) {
    Component::id = id;
}

const string &Component::getName() const {
    return name;
}

void Component::setName(const string &name) {
    Component::name = name;
}

const string &Component::getDescription() const {
    return description;
}

void Component::setDescription(const string &description) {
    Component::description = description;
}

int Component::getStatus() const {
    return status;
}

void Component::setStatus(int status) {
    Component::status = status;
}

time_t Component::getTimeOfDay() {
    return time(0);
}

char *Component::getTimeOfDayUTC(time_t timeOfDay) {
    char *dt;
    tm *gmtm = gmtime(&timeOfDay);
    dt = asctime(gmtm);
    return dt;

}
