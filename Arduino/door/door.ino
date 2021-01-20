#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

#define I2C_SDL    D1
#define I2C_SDA    D2

#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"

const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;

void setup(void) {
  Serial.begin(9600);
  Serial.print("Connecting to: ");
  Serial.println(SSID_NAME);

  Servo servo;
  servo.attach(D5);
   
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PSK);

  while(WiFi.status() != WL_CONNECTED) {  
    delay(500);
  } // When Wemos is not connected, try reconnecting after 500 milliseconds. 
    
  Serial.print("Connected with IP address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(D5, OUTPUT); //to flash the mosfet
  Wire.begin();
  servo.writeMicroseconds(2250);
  delay(500);
  servo.writeMicroseconds(750);
  delay(500);
}

unsigned int outputs=0;
unsigned int state=0;
unsigned counter = 0;
unsigned int last_input=0;
void loop() {
  //flash mosfet output
  digitalWrite(D5,HIGH);
  delay(100); 
  digitalWrite(D5,LOW);
  delay(100);

  /*
  Serial.print("Connecting to: ");
  Serial.print(server_host);
  Serial.print(":");
  Serial.println(port_number);*/   // ---> Only for DEBUG purposes 

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
  } else if((state && !last_input) || ( state && counter > 360)){
    state = last_input;
  }
/*
 * The opening of the door still needs to be implemented go 
 * through the MAX11647 for that make it open during the state == 1. 
 */
  if(state){
    outputs = 0x03;
  }else{
    outputs = 0x00;
    
  }
  
  //Set PCA9554 outputs (IO44-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs << 4));            
  Wire.endTransmission(); 
  Serial.print("Digital out: ");
  Serial.println(outputs&0x0F);

//  delay(500);

  Serial.println("TCP connection will be closed now!");
  client.stop();
}
