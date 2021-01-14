#include <Wire.h>



#define I2C_SDL    D1
#define I2C_SDA    D2

void setup(void) {
  pinMode(D5, OUTPUT);
  Wire.begin();
  Serial.begin(115200);
}

unsigned int outputs=0;
unsigned int state=0;
unsigned counter = 0;
void loop() {
  // put your main code here, to run repeatedly:
   //flash mosfet output
  digitalWrite(D5,HIGH);
  delay(100); 
  digitalWrite(D5,LOW);
  delay(100);

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
  Serial.println(inputs&0x0F);

  if(inputs && state == 0){
    state = 1;
  }

  if((state == 1 && inputs) || ( state == 1 && counter > 360)){
    state = 0;
  }
/*
 * The opening of the door still needs to be implemented go 
 * through the MAX11647 for that make it open during the state == 1. 
 */
  if(ledsOn){
    outputs = 0x03;
  }
  
  //Set PCA9554 outputs (IO44-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(outputs));            
  Wire.endTransmission(); 
  Serial.print("Digital out: ");
  Serial.println(outputs&0x0F);
}
