#include <ArduinoJson.h>

void setup() {
 
  Serial.begin(9600);
  Serial.println("\n");
}
 
void loop() {
  String furniture = "bed";
  int stat = 0;
  const char* data = "{\"type\":\"furniture\",\"status\":status_code}";
  if (Serial.read() == 'j') {
    StaticJsonDocument<96> json_object;
    DeserializationError err = deserializeJson(json_object, data);
    if (err) {
      Serial.print("ERROR: ");
      Serial.println(err.c_str());
    }
//    const char* type = json_object["type"];
//    int number = json_object["status"];
//      Serial.println(type);
//      Serial.println(number);
      json_object["type"] = furniture;
      json_object["status"] = stat;

      char buffer[100];
      serializeJson(json_object, buffer);
      Serial.println(buffer);
  }
}
