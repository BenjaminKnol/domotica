/* Bronnen:
* http://www.danielsoltyka.com/programming/2011/04/15/simple-class-serialization-with-jsoncpp/ ---> With class (OO)
* https://stackoverflow.com/questions/34386807/converting-json-object-to-c-object --> Without classes
* https://linux.tips/programming/how-to-install-and-use-json-cpp-library-on-ubuntu-linux-os ---> How to install JsonCpp
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

  bool serializer(Json::Value& json);
  bool deserializer(Json::Value& json);

  string get_id();
  int get_status();

private:
  string id;
  int status;
};
