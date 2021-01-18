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

void Json_conversion::serializer(string& send_message) {
  Json::Value serializer_json;                      // Create JSON document class and store everything in this object.
  serializer_json["type"] = id;                    // Add value to variable 'id'
  serializer_json["status"] = status;             // Add value status to variable 'status'
  Json::StyledWriter writer;                     // Create writer object from JSON-class
  send_message = writer.write(serializer_json); // Parsing into JSON-Object
}
void Json_conversion::deserializer(string& message) {
  Json::Value deserializer_json;
  Json::Reader reader;
  reader.parse(message, deserializer_json, false);

  id = deserializer_json.get("type", Json::nullValue).asString();      // Get 'id' as a string
  status = deserializer_json.get("status", Json::nullValue).asInt();   // Get 'status' as an int
}

/*
* Getter functions
*/
string Json_conversion::get_id() {
  return id;
}
int Json_conversion::get_status() {
  return status;
}

/*
* Setter functions
*/
void Json_conversion::set_id(string setId) {
  id = setId;
}
void Json_conversion::set_status(int setStatus) {
  status = setStatus;
}
