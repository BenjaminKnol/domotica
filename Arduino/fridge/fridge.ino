#include <Wire.h>
#include <ESP8266WiFi.h>

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
unsigned counter = 0;
unsigned int last_input=0;

void setup(void) {
  Serial.begin(9600);
  //commented out for testing purpose without needing pi
  /*Serial.print("Connecting to: ");
  Serial.println(SSID_NAME);

   
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PSK);

  while(WiFi.status() != WL_CONNECTED) {  
    delay(500);
  } // When Wemos is not connected, try reconnecting after 500 milliseconds. 
    
  Serial.print("Connected with IP address: ");
  Serial.println(WiFi.localIP());
  */
  pinMode(D5, OUTPUT); //to flash the mosfet
  Wire.begin();
}

void loop() {

  readAnalogSensors();
  /*
  Serial.print("Connecting to: ");
  Serial.print(server_host);
  Serial.print(":");
  Serial.println(port_number);*/   // ---> Only for DEBUG purposes 
/* commented out for testing purpose without needing pi
  WiFiClient client; // ---> Create a TCP-connection 
  if (!client.connect(server_host, port_number)) {
    Serial.println("Connection has failed");
    delay(5000);  // ---> Waiting 5 seconds to re-connecting too server.
    return;
  }

   String line;
   client.setTimeout(200);
   line = client.readStringUntil('\r'); // --> Read line from server
   Serial.println(line);
  */
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
  Serial.print("Digital in: ");
  inputs = inputs & 0x03;
  Serial.println(inputs);
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
  
  //Set PCA9554 outputs (IO44-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs << 4));            
  Wire.endTransmission(); 
  Serial.print("Digital out: ");
  Serial.println(outputs&0x0F);

//  delay(500);
/* commented out for testing purposes
  Serial.println("TCP connection will be closed now!");
  client.stop();
*/
}

void readAnalogSensors() {            //Read analog 10bit inputs 0 from MAX11647
  Wire.requestFrom(0x36, 4);              //why 4? maybe change to 2   
  unsigned int ai0 = Wire.read()&0x03;    //analog input 0, wire.read reads only 8 bits
  ai0=ai0<<8;                             //bitshift with 8 because the analog input is 10 bits
  ai0 = ai0|Wire.read();  
  unsigned int ai1 = Wire.read()&0x03;
  Serial.print("analog0 is: ");
  Serial.println(ai0); 
  Serial.println("");
  Serial.print("analog1 is: ");
  Serial.println(ai1); 
  Serial.println("");
  if (ai0 != 0) // If analog input is not zero
  {
    Vo = (analogRead(ai0) + analogRead(ai1)) / 2;            //reads voltage of the analog pin (test if there's actually 2)
    R2 = R1 * (1023.0 / (float)Vo - 1.0);                 //resistance = known resistor value * (1023.0 / voltage -1)
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));   //calculates temperature in Kelvin
    Tc = T - 273.15;                                      //converts temp to celcius
    Serial.print("Temperature: "); 
    Serial.print(Tc);
    Serial.println(" C");
  }else{
    Serial.print("No temperature detected? Sumthing is borked");
  }
}