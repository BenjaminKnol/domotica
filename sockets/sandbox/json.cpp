#include "json.h"

using namespace std;

Json::Json() {

}
string Json::split(string message) {
  while ((index = message.find(delimiter)) != std::string::npos) {
      id = message.substr(0, index);
      id = id.substr(1, -1);
      message.erase(0, index + delimiter.length());
  }
  to_int(message);
  return id;
}
int Json::to_int(string message) {
  message = message.substr(0, message.size()-1);
  if (message.compare("1") == 0) {
    status = 1;
  } else {
    status = 0;
  }
   return status;
}
