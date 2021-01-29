/*
 * This file causes the Raspberry Pi to receive and send a JSON Object
 * and extract it to/from the assigned variables.
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *
 * Used sources: https://stackoverflow.com/questions/34386807/converting-json-object-to-c-object
 *               http://www.danielsoltyka.com/programming/2011/04/15/simple-class-serialization-with-jsoncpp/
 *               https://linux.tips/programming/how-to-install-and-use-json-cpp-library-on-ubuntu-linux-os      ---> How to install JsonCpp
 */
#include <jsoncpp/json/json.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

using namespace std;

class Json_conversion {
public:
    Json_conversion(); // Default constructor

    // Do functions
    void serializer(string &send_message);
    void deserializer(string &message);

    // Getter functions
    int get_unique_id();
    int get_button();
    int get_sensor();

private:
    int unique_id;
    int button;
    int sensor;
};
