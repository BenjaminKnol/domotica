#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ArduinoJson.h>

#define I2C_SDL    D1
#define I2C_SDA    D2

#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"

const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;
Servo servo;
unsigned int outputs=0;
unsigned int state=0;
uint16_t counter = 0;
unsigned int last_input=0;
unsigned int nextState=1;

String json_data(String, int);

String json_data(String furniture, int status) {
  const char* data = "{\"id\":\"furniture\",\"status\":status_code}"; // Create JSON skeleton   
  StaticJsonDocument<96> json_object;     // Create JSON object
  json_object["id"] = furniture;        // Modify value in JSON object based on key name
  json_object["status"] = status;      // Modify value in JSOB object based on key name
  char send_data[100];              
  serializeJson(json_object, send_data); // Convert JSON Object to a character string. 

  return send_data;
}

void setup(void) {
  Serial.begin(9600);
  Serial.print("Connecting to: ");
  Serial.println(SSID_NAME);
  
  servo.attach(D5);
   
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PSK); 
  
  pinMode(D5, OUTPUT); //to flash the mosfet
  Wire.begin();
}

void loop() {
   while(WiFi.status() != WL_CONNECTED) {  
    delay(500);
  } // When Wemos is not connected, try reconnecting after 500 milliseconds.

  WiFiClient client; // ---> Create a TCP-connection 
  if (!client.connect(server_host, port_number)) {
    Serial.println("Connection has failed");
    delay(5000);  // ---> Waiting 5 seconds to reconnect to server.
    return;
  }

   String line;
   client.setTimeout(200);
   line = client.readStringUntil('\r'); // --> Read line from server
  
  //Config PCA9554
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board). 
  //IO0-IO3 as input, IO4-IO7 as output.
  /* could move this to setup for end product */
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));          
  Wire.write(byte(0x0F));         
  Wire.endTransmission();

  //Read PCA9554 outputs (IO40-IO3)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  
//  Serial.print("Digital in: ");
  inputs = inputs & 0x03;
//  Serial.println(inputs);

  if (last_input) {
    if (inputs || line.indexOf("0") >= 0) {
      last_input = 0;
    } 
  } else {
    if (inputs || line.indexOf("1") >= 0) {
      last_input = 1;
    }
  }
  if((last_input && !state)){
    state = last_input;
  } else if((state && !last_input) || ( state && counter > 3150)){
    state = last_input;
  }
/*
 * The opening of the door still needs to be implemented go 
 * through the MAX11647 for that make it open during the state == 1. 
 */
  if(state){
    if(nextState == 1){
      nextState = 0;
      client.println(json_data("6", 1));
    }
    outputs = 0x03;
    servo.write(165);
    counter++;
  }else{
    if(nextState == 0){
      nextState = 1;
      client.println(json_data("6", 0));
    }
    outputs = 0x00;
    servo.write(84);
    counter = 0;
  }
  
  //Set PCA9554 outputs (IO44-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs << 4));            
  Wire.endTransmission(); 
//  Serial.print("Digital out: ");
//  Serial.println(outputs&0x0F);

//  Serial.println("TCP connection will be closed now!");
  client.stop();
}
