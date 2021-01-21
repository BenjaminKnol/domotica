//
// Created by Asus on 20-1-2021.
//

#ifndef CLASSSTRUCTURE_COMPONENT_H
#define CLASSSTRUCTURE_COMPONENT_H

#include <string>

using namespace std;

class Component {

private:
    int id;
    string name;
    string description;
    int status;

public:


    int getId() const;

    void setId(int id);

    const string &getName() const;

    void setName(const string &name);

    const string &getDescription() const;

    int getStatus() const;

    void setStatus(int status);

    void setDescription(const string &description);
};


#endif //CLASSSTRUCTURE_COMPONENT_H
