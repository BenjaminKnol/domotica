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
#include "Json_conversion.h"

Json_conversion::Json_conversion() {
}
void Json_conversion::deserializer(string &message) {
    Json::Value deserializer_json;                                                // Create JSON document class and store everything in this object.
    Json::Reader reader;
    reader.parse(message, deserializer_json);
    uniqueId = deserializer_json.get("guid", Json::nullValue).asString();
    id = deserializer_json.get("id", Json::nullValue).asString();
    status = deserializer_json.get("status", Json::nullValue).asInt();
}

/*
* Getter functions
*/
string Json_conversion::getUniqueId() {
    return uniqueId;
}

string Json_conversion::getId() {
    return id;
}

int Json_conversion::getStatus() {
    return status;
}
