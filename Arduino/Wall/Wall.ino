/*
 * This file (sketch) ensures that the Wemos D1 Mini has a socket
 * connection with the Raspberry Pi 4, which acts as a hotspot / server. Therefore, it sends
 * a status update from the wall.
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *
 */
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ArduinoJson.h>

#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"
#define I2C_SDL    D1
#define I2C_SDA    D2

WiFiClient client; // Create TCP connection object

/* Global variables */
const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;
const char unique_id = 'w';  /* Unique identification for Wemos*/
const String check_unique_id = "unique_id";       /* Check whether received message matches with variable */
const String check_verification = "Acknowledge";  /* Check whether received message matches with variable */
String line;
unsigned int ldr = 0;
unsigned int potentiometer = 0;
int lastInputPotmeter = 0;
int lastInputLDR = 0;

/* Prototypes */
void initialize();
void connectToHotspot();
String read_message(WiFiClient received_message);
void readAnalogValues(unsigned int, unsigned int);

void setup(void) {
  initialize();
  connectToHotspot();
}
void loop(void) {
  line = ""; // Make sure 'line' is empty.
  if (client.connect(server_host, port_number)) {
    line = read_message(client);
    if (line == check_unique_id){ // Tell the RPi which ID you have
      client.print(String(unique_id));
    }
    line = read_message(client);
    if (line == check_verification) {
//      Serial.println(line); // DEBUG-only
      Serial.println("Connection has been established and verified.");

      /* When connection with RPi is established read and send actual data. */
      while (client.connected()) {
        line = read_message(client);
        Serial.println(line);
      }
    } else{
      Serial.println("Could not verify Wemos with RPi.");
    }
    Serial.println("No connection could be established.");
    client.stop();
  }
}
void initialize(){
  Serial.begin(9600);
  Wire.begin();
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  // ------------------------------  Basic configuration

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
void connectToHotspot() {
  // Start code - connecting to Raspberry Pi hotspot
  Serial.print("Connecting to: ");
  Serial.println(SSID_NAME);
  WiFi.mode(WIFI_STA); /* Set Wemos in station and not Access Point */
  WiFi.begin(SSID_NAME, SSID_PSK);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  } /* When Wemos is not connected, try reconnecting after 500 milliseconds.*/
  Serial.print("Connected with IP address: ");
  Serial.println(WiFi.localIP());
}
String read_message(WiFiClient received_message) { // Read message from server (Pi)
  return received_message.readStringUntil('\r'); // --> Read line from server
}
void readAnalogValues(unsigned int ldr, unsigned int potentiometer) {
  Wire.requestFrom(0x36, 4);
  ldr = Wire.read()&0x03;
  ldr=ldr<<8;
  ldr = ldr|Wire.read();
//  Serial.print("analog in 0: ");
//  Serial.println(LDR);
  potentiometer = Wire.read()&0x03;
  potentiometer=potentiometer<<8;
  potentiometer = potentiometer|Wire.read();
//  Serial.print("analog in 1: ");
//  Serial.println(potentiometer);

  if (potentiometer != lastInputPotmeter && ldr != lastInputLDR) {
    Serial.print("Potentiometer status: ");
    Serial.println(potentiometer);
    Serial.print("LDR status: ");
    Serial.println(ldr);
  }
  lastInputPotmeter = potentiometer;
  lastInputLDR = ldr;
}
