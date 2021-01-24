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
bool check_number(string str) {
    if (isdigit(str[0]) == false) {
      return false;
    }
   for (int i = 0; i < str.length(); i++){
    if (isdigit(str[i]) == false) {
      return false;
    }
   }
  return true;
}
void Json_conversion::deserializer(string& message) {
  Json::Value deserializer_json;                                                // Create JSON document class and store everything in this object.
  Json::Reader reader;
  reader.parse(message, deserializer_json);
  unique_id = deserializer_json.get("guid", Json::nullValue).asInt();
  id = deserializer_json.get("id", Json::nullValue).asString();              // Add value to variable 'id'
  status = deserializer_json.get("status", Json::nullValue).asBool();       // Add value status to variable 'status'
  cout << "String: " << id << endl;
  if (check_number(id)) {
    cout << "int: " << id << endl;
     convert_id = stoi(id);// Necessary since id is received as string and switch-statements can only check with integers or char
 }
}


/*
* Getter functions
*/
int Json_conversion::get_unique_id() {
  return unique_id;
}
int Json_conversion::get_id() {
  return convert_id;
}
int Json_conversion::get_status() {
  return status;
}

/*
* Setter functions
*/
void Json_conversion::set_convert_id(int new_int) {
 convert_id = new_int;
}
