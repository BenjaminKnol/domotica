#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ArduinoJson.h>

#define I2C_SDL    D1
#define I2C_SDA    D2

#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"

Servo servo;
unsigned int outputs = 0;
uint16_t counter = 0;
unsigned int lastButtonState = 0;
unsigned int inputs, control, buttonState, toPi;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;



/* Global variables */
const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;
const String unique_id = "door0";  /* Unique identification for Wemos*/
const String check_unique_id = "unique_id";       /* Check whether received message matches with variable */
const String check_verification = "Acknowledge";  /* Check whether received message matches with variable */
String line;
void sendMessage(int);
//String json_data(int);

WiFiClient client; // Create TCP connection object
void connectToHotspot();
String readMessage(WiFiClient received_message);
int readPCAInput();


//String json_data(String furniture, int status) {
//  const char* data = "{\"id\":\"furniture\",\"status\":status_code}"; // Create JSON skeleton
//  StaticJsonDocument<96> json_object;     // Create JSON object
//  //json_object["id"] = furniture;        // Modify value in JSON object based on key name
//  json_object["status"] = status;      // Modify value in JSOB object based on key name
//  char send_data[100];
//  serializeJson(json_object, send_data); // Convert JSON Object to a character string.
//
//  return send_data;
//}

void setup(void) {
  Serial.begin(9600);
  connectToHotspot();
  servo.attach(D5);
  initialize();
  pinMode(D5, OUTPUT); //to flash the mosfet
  Wire.begin();
}

void loop() {
  inputs = readPCAInput();
  if (inputs != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (inputs != buttonState) {
      buttonState = inputs;

      if (buttonState == 1) {
        toPi = !toPi;
      }
    }
  }
  if (buttonState != lastButtonState) {
    sendMessage(toPi);
    line = readMessage(client);
    control = line.toInt();

    if (control) {
      outputs = 0x03;
      servo.write(165);
      lastButtonState = control;
      //counter++;
    } else {
      outputs = 0x00;
      servo.write(84);
      //counter = 0;
      lastButtonState = control;
    }
  }
}

void initialize() {
  //Config PCA9554
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board).
  //IO0-IO3 as input, IO4-IO7 as output.
  /* could move this to setup for end product */
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();


}

void writePCAOutput() {
  //Set PCA9554 outputs (IO44-IO7)
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(outputs << 4));
  Wire.endTransmission();
}
int readPCAInput() {
  //Read PCA9554 outputs (IO40-IO3)
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  inputs = Wire.read();
  //  Serial.print("Digital in: ");
  inputs = inputs & 0x03;
  //  Serial.println(inputs);
  return inputs;
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

void sendMessage(int message) {
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
