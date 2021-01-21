//Niek Hutten
//Test to see if reading analog ForceSensor from Bed hardware and turn on some leds when it is pressed stronger than a certain value
#include <Wire.h>



#define I2C_SDL    D1
#define I2C_SDA    D2

// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 4.98;                     // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0;                 // Measured resistance of 3.3k resistor


void setup(void) {
  Wire.begin();
  Serial.begin(115200);
  flash_Mosfet();
  config_PCA9554();
  config_Max11647(); 
}


unsigned int outputs=5;                   //testvalue 
void loop(void) { 
  readAnalogForceSensor();
}

void flash_Mosfet() {
  digitalWrite(D5,HIGH);
  delay(100); 
  digitalWrite(D5,LOW);
  delay(100); 
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
  Wire.write(byte(outputs<<0));            
  Wire.endTransmission(); 
  Serial.print("Digital out: ");
  Serial.println(outputs&0x0F);
  outputs++;
  readPCA9554Outputs();
}  


  
  void readPCA9554Outputs(){              //Read PCA9554 outputs (IO40-IO3)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  
  Serial.print("Digital in: ");
  Serial.println(inputs&0x0F);
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
        setPCA9554Outputs();              //call function to turn leds on
      } 
    }
  }
  else{
    Serial.print("No pressure detected? Sumthing is borked");
  }
}
