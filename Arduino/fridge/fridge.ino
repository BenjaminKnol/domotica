#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>  // --> JSON library

#define I2C_SDL    D1
#define I2C_SDA    D2

#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"

const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

unsigned int outputs=0;
unsigned int state=0;
unsigned int counter = 0;
unsigned int last_input=0;
unsigned int door;

WiFiClient client; // ---> Create a TCP-connection 

void activateCooling();
void doorAlarm();
void connectToHotspot();
void sendMessage();
String readMessage(double);

//String json_data(String furniture, int status) {
//  const char* data = "{\"id\":\"furniture\",\"status\":status_code}"; // Create JSON skeleton   
//  StaticJsonDocument<96> json_object;     // Create JSON object
//  json_object["id"] = furniture;        // Modify value in JSON object based on key name
//  json_object["status"] = status;      // Modify value in JSOB object based on key name
//  char send_data[100];              
//  serializeJson(json_object, send_data); // Convert JSON Object to a character string. 
//
//  return send_data;
//}

void setup(void) {
  Serial.begin(9600);
  connectToHotspot();
   

}

void loop() {

  Wire.begin();
  readAnalogSensors();
  

   String line;
   client.setTimeout(200);
   line = client.readStringUntil('\r'); // --> Read line from server
   Serial.println(line);
 
  //Config PCA9554
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board). 
  //IO0-IO3 as input, IO4-IO7 as output.
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
  //Serial.print("Digital in: ");
  inputs = inputs & 0x03;
  //Serial.println(inputs);

  if (inputs == 2 ){
    doorAlarm();
  }else if (door == 1) {
    door = 0;
    client.println(json_data("2", 0));
    counter = 0;
  }else {
    counter = 0;  
  }
/*
 * 
 * through the MAX11647 for that make it open during the state == 1. 
 */
 /*commented out for testing without pi
  if(state){
    outputs = 0x03;
    
  }else{
    outputs = 0x00;
    
  }
  */
  

  delay(1000);
  Serial.println(counter);
/* commented out for testing purposes
  Serial.println("TCP connection will be closed now!");
  client.stop();
*/
}

void readAnalogSensors() {            //Read analog 10bit inputs 0 from MAX11647
  Wire.requestFrom(0x36, 4);              // 4 needed since two 10 bit ints need to be read in byte size.  
  unsigned int ai0 = Wire.read()&0x03;    //analog input 0, wire.read reads only 8 bits
  ai0=ai0<<8;                             //bitshift with 8 because the analog input is 10 bits
  ai0 = ai0|Wire.read();  
  unsigned int ai1 = Wire.read()&0x03;
  ai1=ai1<<8;                             //bitshift with 8 because the analog input is 10 bits
  ai1 = ai1|Wire.read();
  /*
  Serial.print("analog0 is: ");
  Serial.println(ai0); 
  Serial.println("");
  Serial.print("analog1 is: ");
  Serial.println(ai1); 
  Serial.println("");
  */
  Vo = (ai0 + ai1) / 2;            //reads voltage of the analog pin (test if there's actually 2)
  R2 = R1 * (1023.0 / (float)Vo - 1.0);                 //resistance = known resistor value * (1023.0 / voltage -1)
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));   //calculates temperature in Kelvin
  Tc = T - 273.15;                                      //converts temp to celcius
  Serial.print("Temperature: "); 
  Serial.print(Tc);
  Serial.println(" C");
  
  if(Tc > 4){
    activateCooling();
  }else {
    //Serial.print("cooling inactive");
    digitalWrite(D5,LOW);      //peltier off
  }
}

void activateCooling(){
  outputs = 0x01;             //0x1 is de fan
  digitalWrite(D5,HIGH);      //peltier on
  //Serial.println("cooling active");
  //Serial.print("");
    //Set PCA9554 outputs (IO44-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs << 4));            
  Wire.endTransmission(); 
  //Serial.print("Digital out: ");
  //Serial.println(outputs&0x0F);
  
}

void doorAlarm(){
  if (counter > 30) {
    if (door == 0) {
      //Serial.println("YOU FORGOT CLOSE THE FRIDGE DOOR!"); 
      client.println(json_data("2", 1));
    }
    door = 1;
  }
  counter++;
}


void connectToHotspot() {
  // Start code - connecting to Raspberry Pi hotspot
  Serial.print("Connecting to: ");
  Serial.println(SSID_NAME);
  WiFi.mode(WIFI_STA); /* Set Wemos in station and not Access Point */
  WiFi.begin(SSID_NAME, SSID_PSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  } /* When Wemos is not connected, try reconnecting after 500 milliseconds.*/
  Serial.print("Connected with IP address: ");
  Serial.println(WiFi.localIP());

  // ---------------------------------- One time socket identification with RPi
  if (!client.connect(server_host, port_number)) {
    Serial.println("No connection could be established.");
    client.stop();
  } else {
    client.print(String(unique_id));
    line = readMessage(client);
    if (line == check_verification) {
      //      Serial.println(line); // DEBUG-only
      Serial.print(unique_id);
      Serial.print(": Is verified with: ");
      Serial.println(client.remoteIP()); // Printing server IP-address
    } else {
      Serial.println("Could not verify Wemos with RPi.");
    }
  }
}
String readMessage(WiFiClient received_message) { // Read message from server (Pi)
  return received_message.readStringUntil('\r'); // --> Read line from server
}
void sendMessage(String message) {
  if (client.connect(server_host, port_number)) {
    client.print(unique_id);
    line = readMessage(client); // Receive Ack
//    Serial.println(line); // DEBUG-Only

    while (client.connected()) {
      line = readMessage(client);
//      Serial.println(line); // DEBUG-Only
      if (line == "RTR") { // Check if received line is equal to RTR
        client.print(message); // Send status update
        break; // Break out the while loop
      }
    }
  }
}
