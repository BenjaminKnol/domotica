#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>  // --> JSON library

#define I2C_SDL    D1
#define I2C_SDA    D2

#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"

const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;

unsigned int led = 1;
unsigned int buzzer = 0x01;

WiFiClient client; // ---> Create a TCP-connection 

void readGasSensor();

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

  
  setPCA9554Outputs();
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PSK);

}

void loop() {

  while(WiFi.status() != WL_CONNECTED) {  
    delay(500);
  } // When Wemos is not connected, try reconnecting after 500 milliseconds. 

  pinMode(D5, OUTPUT); //to flash the mosfet
  Wire.begin();
  
  readGasSensors();
  /*
  Serial.print("Connecting to: ");
  Serial.print(server_host);
  Serial.print(":");
  Serial.println(port_number);*/   // ---> Only for DEBUG purposes 
  //commented out for testing purpose without needing pi
  
  if (!client.connect(server_host, port_number)) {
    Serial.println("Connection has failed");
    delay(5000);  // ---> Waiting 5 seconds to re-connecting too server.
    return;
  }

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
  Serial.print("Digital in: ");
  inputs = inputs & 0x03;
  Serial.println(inputs);

  delay(1000);
/* commented out for testing purposes
  Serial.println("TCP connection will be closed now!");
  client.stop();
*/
}

void setPCA9554Outputs(){                 //Set PCA9554 outputs (IO4-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(led<<4));               //should turn on led, bit lost so test this
  Wire.endTransmission();
}

void readGasSensors() {                   //Read analog 10bit inputs 0 from MAX11647
  Wire.requestFrom(0x36, 2);              // 2 needed   
  unsigned int ai0 = Wire.read()&0x03;    //analog input 0, wire.read reads only 8 bits
  ai0=ai0<<8;                             //bitshift with 8 because the analog input is 10 bits
  ai0 = ai0|Wire.read();  
  
  Serial.print("analog0 is: ");
  Serial.println(ai0); 
  Serial.println("");

  if(ai0 > 0){
    activateBuzzer();
  }else{
    Serial.print("buzzer inactive");
  }
}

void activateBuzzer(){   
  tone(buzzer, 500); // Send 0.5KHz sound signal            TEST THIS, no idea if it works
  delay(1000);        // for 1 sec
  tone(buzzer, 1000); // Send 1KHz sound signal
  delay(1000);        // for 1 sec
  noTone(buzzer);     // Stop sound
  Serial.println("Should pause buzzing!");
  delay(1000);        // for 1sec
 
  Serial.println("Should be buzzing!");
  Serial.print("");
    //Set PCA9554 outputs (IO4-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs << 4));            
  Wire.endTransmission(); 
  Serial.print("Digital out: ");
  Serial.println(outputs&0x0F);
}
