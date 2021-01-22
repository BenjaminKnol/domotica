#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>  // --> JSON library

/* Possible LED libraries:
 *  https://www.arduino.cc/reference/en/libraries/rgb_led/
 *  
*/

#define I2C_SDL    D1
#define I2C_SDA    D2

#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"

void flash_Mosfet();
String json_data(String, int);
void config_PCA9554();
void setPCA9554Outputs();
void readPCA9554Outputs();
void config_Max11647();
void turnOnLight();
void turnOffLight();



const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;
String line;
WiFiClient client; // ---> Create a TCP-connection
unsigned int state=0; 
unsigned int inputs=0;
unsigned int activityCounter=0;
unsigned int firstRun = 1;


void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  flash_Mosfet();
  
  config_PCA9554();
  config_Max11647();

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PSK);
}

void loop() {
  while(WiFi.status() != WL_CONNECTED) {  
    delay(500);
  } // When Wemos is not connected, try reconnecting after 500 milliseconds.
  if (!client.connect(server_host, port_number)) {
    Serial.println("Connection has failed");
    delay(5000);  // ---> Waiting 5 seconds to re-connecting too server.
    return;
  }
    
  client.setTimeout(200);
  line = client.readStringUntil('\r'); // --> Read line from server
  Serial.println(line);

  if(line.indexOf("Allowed") >= 0){ //apperently its currently between 17:00 - 9:00 and thus the light is able to be turned on.
    readPCA9554Outputs();
    if(inputs){
      activityCounter =0;
      turnOnLight();
    }
    activityCounter++;
  }else if(state == 1 && (line.indexOf("Allowed") == -1 || activityCounter > 9000)){
      turnOffLight();
  }
  if(line.indexOf("0") >= 0){
    turnOffLight();
  }
  if(line.indexOf("1") >= 0){
    turnOnLight();
  }
}

/* -------------------------------------------------------------------------------------------------------------------------------------------------------*/
void flash_Mosfet() {
  pinMode(D5, OUTPUT);
  digitalWrite(D5,HIGH);
  delay(100); 
  digitalWrite(D5,LOW);
  delay(100); 
}

String json_data(String furniture, int status) {
  const char* data = "{\"id\":\"furniture\",\"status\":status_code}"; // Create JSON skeleton   
  StaticJsonDocument<96> json_object;     // Create JSON object
  json_object["id"] = furniture;        // Modify value in JSON object based on key name
  json_object["status"] = status;      // Modify value in JSOB object based on key name
  char send_data[100];              
  serializeJson(json_object, send_data); // Convert JSON Object to a character string. 

  return send_data;
}

void config_PCA9554() {                   //IO0-IO3 as input, IO4-IO7 as output.
  Wire.beginTransmission(0x38);           //address I2C for PCA9554
  Wire.write(byte(0x03));            
  Wire.write(byte(0x0F));         
  Wire.endTransmission();
}


void setPCA9554Outputs(){                 //Set PCA9554 outputs (IO4-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs<<4));            
  Wire.endTransmission(); 
//  Serial.print("Digital out: ");
//  Serial.println(outputs&0x0F);
}
  
void readPCA9554Outputs(){              //Read PCA9554 outputs (IO40-IO3)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  inputs = Wire.read() & 0x01;  
//  Serial.print("Digital in: ");
//  Serial.println(inputs&0x0F);
  }  

void config_Max11647() {
  Wire.beginTransmission(0x36);           //address I2C for MAX11647
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));                 //configuration byte   
  Wire.endTransmission(); 
}

void turnOnLight(){ //[PLACEHOLDER] Until able to figure out just what led is used I will leave the implementation of turning on the light empty.
  state = 1;
  if(firstRun){
    firstRun = 0;
    client.println(json_data("5", 1));
  }
}

void turnOffLight(){ //[PLACEHOLDER] Until able to figure out just what led is used I will leave the implementation of turning off the light empty.
  state = 0;
  if(firstRun){
    firstRun = 0;
    client.println(json_data("5", 0));
  }
}
