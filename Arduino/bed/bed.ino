//Niek Hutten
//Test to see if reading analog ForceSensor from Bed hardware and turn on some leds when it is pressed stronger than a certain value

/*void loop(void){
    readAnalogForceSensor(); //nice idea but needs a lot of reconstruction
  }*/

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

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
void readAnalogForceSensor();
void lightControl();
void inBedControl();


// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 4.98;                     // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0;                 // Measured resistance of 3.3k resistor

unsigned int outputs=0;
unsigned int state=0;
uint16_t OutOfBedcounter = 0;
uint16_t lightCounter = 0;
unsigned int inputs=0;
unsigned int lastInput;
unsigned int firstRun=2;
unsigned int inBed = 0;
String line;

WiFiClient client; // ---> Create a TCP-connection 

void setup(void) {
  Wire.begin();
  Serial.begin(115200);
  
  flash_Mosfet();
  
  config_PCA9554();
  config_Max11647();

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PSK);
}

void loop(void) {
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

  lightControl();

  inBedControl();
  
}

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

void readAnalogForceSensor() {            //Read analog 10bit inputs 0 from MAX11647
  Wire.requestFrom(0x36, 2);              //2 because only 1 analog input needs to be read
  unsigned int ai0 = Wire.read()&0x03;    //analog input 0, wire.read reads only 8 bits
  ai0=ai0<<8;                             //bitshift with 8 because the analog input is 10 bits
  ai0 = ai0|Wire.read();  
  Serial.print("analog in 0: ");
  Serial.println(ai0); 
  Serial.println("");
  
  if (ai0 != 0) // If analog input is not zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV = ai0 * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of FSR datasheet:
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) {         //
      force = (fsrG - 0.00075) / 0.00000032639;
    }else{
      force =  fsrG / 0.000000642857;
      Serial.println("Force: " + String(force) + " g");
      Serial.println("");
      if (force > 1000){          //5000 should be 5000 gram, change value depending on test results
        inBed = 1;
      }else{
        inBed = 0;
      }
    }
  }
  else{
    Serial.print("No pressure detected? Sumthing is borked");
  }
}

void lightControl(){
  readPCA9554Outputs();
  if (lastInput) {
    if (inputs || line.indexOf("0") >= 0) {
       lastInput = 0;
    } 
  } else {
    if (inputs || line.indexOf("1") >= 0) {
      lastInput = 1;
    }
  }

  if(lastInput){
    outputs |= 0b00000001;
  }
  if(lastInput || lightCounter > 9000){
    outputs &= 0b11111110;
  }
  setPCA9554Outputs();
}

void inBedControl(){
  if(!inBed){
    if(OutOfBedcounter > 1500){
      if(firstRun == 1){
        firstRun = 0;
        client.println(json_data("6", 0)); // for now the assumption is that we only store whether user is out of bed. if we need to change this we may need to add another field
      }
    }
    OutOfBedcounter++;
  }else if(inBed){
    if(firstRun == 1){
      firstRun = 0;
      client.println(json_data("6", 1));
    }
    OutOfBedcounter = 0;
  }
}
