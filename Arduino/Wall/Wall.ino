/*
 * This file (sketch) ensures that the Wemos D1 Mini has a socket 
 * connection with the Raspberry Pi 4, which acts as a hotspot / server.
 * Therefore, this file sends a status update about wall to RPi server. 
 * 
 * Authors: 
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *    
 * Used sources: https://diyprojects.io/get-started-with-arduinojson-v6-arduino-library-for-handling-json-objects/#.YARby-hKiMp --> JSON
 *               https://www.youtube.com/watch?v=nfr6wddRRxo ---> JSON (video)
 */
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ArduinoJson.h>  // --> JSON library

#define I2C_SDL    D1
#define I2C_SDA    D2
#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"

const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;

WiFiClient client; // ---> Create a TCP-connection object

// Prototypes
void connectingToHotspot();
void connectingToSocketServer();
void initialize();
void setDigitalOutput();
void readDigitalOutput();
String json_data(int potentiometer, int LDR);
String readData();
void sendingData(int potentiometer, int LDR);

// Global variables 
unsigned int outputs = 0;
unsigned int inputs = 0;
int lastInputPotmeter = 0;
int lastInputLDR = 0;

void setup() {
  initialize();            // initialize I2C address 
  connectingToHotspot();  // Connect to WiFi hotspot 
}

void loop() {
  String message = readData();
  if (!(message.isEmpty())) {
    setDigitalOutput();
  }
}
String json_data(int potentiometer, int LDR) {
  const char* data = "{\"id\":\4\",\"potentiometer\":potentiometer\",\"LDR\":LDR\"}"; // Create JSON skeleton   
  StaticJsonDocument<96> json_object;                 // Create JSON object
  json_object["potentiometer"] = potentiometer;      // Modify value in JSOB object based on key name
  json_object["LDR"] = LDR;                         // Modify value in JSOB object based on key name
  char send_data[100];              
  serializeJson(json_object, send_data); // Convert JSON Object to a character string. 

  return send_data;
}
void initialize() {
  pinMode(D4, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  // ------------------------------  Basic configuration
 
  pinMode(D5, OUTPUT);
  digitalWrite(D5,HIGH);
  delay(100); 
  digitalWrite(D5,LOW);
  delay(100); 
  // ------------------------------  Flash Mosfet

  Wire.beginTransmission(0x38);         
  Wire.write(byte(0x03));            
  Wire.write(byte(0x0F));         
  Wire.endTransmission();
  // ------------------------------  address I2C for PCA9554
}
void connectingToHotspot() {
   WiFi.mode(WIFI_STA);
   WiFi.begin(SSID_NAME, SSID_PSK);

   while(WiFi.status() != WL_CONNECTED) { // Connecting to hotspot 
     delay(500);
   } // When Wemos is not connected, try reconnecting after 500 milliseconds.
//   Serial.print("Connected with IP address: ");
//   Serial.println(WiFi.localIP());
}
void connectingToSocketServer() {
  if (!client.connect(server_host, port_number)) {
    Serial.println("Connection has failed");
    delay(5000);  // ---> Waiting 5 seconds to re-connecting too server.
    return;
  }
}
String readData() {
  connectingToSocketServer();
  String line = client.readStringUntil('\r'); // --> Read line from server
  if (!(line.isEmpty())) {
    Serial.println(line);
  }
  return line;
  client.stop();
}
void sendingData(int potentiometer, int LDR) {
  connectingToSocketServer();
  if (client.connected()) { // ---> Send data to server (RPi)
    client.println(json_data(potentiometer, LDR));
  }
  client.stop();
}
void setDigitalOutput() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs<<4));            
  Wire.endTransmission(); 
//  Serial.print("Digital out: ");
//  Serial.println(outputs&0x0F);
  // ------------------------------  Set Digital Output
}
void readDigitalOutput() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  inputs = Wire.read() & 0x01;  
//  Serial.print("Digital in: ");
//  Serial.println(inputs&0x0F);
  // ------------------------------  Set PCA9554 read outputs  
}
void readAnalogValues() {
  Wire.requestFrom(0x36, 4);   
  unsigned int LDR = Wire.read()&0x03;  
  LDR=LDR<<8;
  LDR = LDR|Wire.read();  
//  Serial.print("analog in 0: ");
//  Serial.println(LDR);   
  unsigned int potentiometer = Wire.read()&0x03;  
  potentiometer=potentiometer<<8;
  potentiometer = potentiometer|Wire.read(); 
//  Serial.print("analog in 1: ");
//  Serial.println(potentiometer); 
  
  if (potentiometer != lastInputPotmeter && LDR != lastInputLDR) {
    sendingData(potentiometer, LDR);
  }
  lastInputPotmeter = potentiometer;
  lastInputLDR = LDR;
}
