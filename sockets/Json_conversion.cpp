#include "Json_conversion.h"

Json_conversion::Json_conversion() {

}
// bool Json_conversion::Serializer(Json::Value& json) {
//
// }
bool Json_conversion::deserializer(Json::Value& json) {
  Json::Value deserializer_json;
  Json::Reader reader;
  reader.parse(json, deserializer_json, false);
  Json::Value id = deserializer_json.get("type", Json::nullValue).asString();      // Get 'id' as a string
  Json::Value status = deserializer_json.get("status", Json::nullValue).asInt();   // Get 'status' as an int

  return true;
}
string Json_conversion::get_id() {
  return id;
}
int Json_conversion::get_status() {
  return status;
}
