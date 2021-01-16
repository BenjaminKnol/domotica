/*
 * This file (sketch) ensures that the Wemos D1 Mini has a socket 
 * connection with the Raspberry Pi 4, which acts as a hotspot / server.
 * 
 * Authors: 
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 * Versie: 1.0 ---> Set TCP/IP connection between WEMOS en RPi4
 *    
 * Used sources: https://stackoverflow.com/questions/62951017/i-want-to-add-variable-into-json-object-in-arduino --> JSON
 */
#include <ESP8266WiFi.h>

#define SSID_NAME "PJSDV_Grp5_IIHS"
#define SSID_PSK  "Welkom#1"

const char* server_host = "172.16.0.1";
const uint16_t port_number = 9002;

WiFiClient client; // ---> Create a TCP-connection 

String convert_to_json(String furniture, int stat) {
   return "{\"" + furniture + "\":\"" + String(stat) + "\"}";
}
void setup() {
  Serial.begin(9600);

  // Start code - connecting to Raspberry Pi hotspot
    Serial.print("Connecting to: ");
    Serial.println(SSID_NAME);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_NAME, SSID_PSK);
    
    while(WiFi.status() != WL_CONNECTED) {  
      delay(500);
    } // When Wemos is not connected, try reconnecting after 500 milliseconds. 
    
    Serial.print("Connected with IP address: ");
    Serial.println(WiFi.localIP()); 

    Serial.print("Connecting to: ");
    Serial.print(server_host);
    Serial.print(":");
    Serial.println(port_number);   // ---> Only for DEBUG purposes   
}

void loop() {  
    if (!client.connect(server_host, port_number)) {
    Serial.println("Connection has failed");
    delay(5000);  // ---> Waiting 5 seconds to re-connecting too server.
    return;
   } 
   
  if (client.connected()) { // ---> Send data to server (RPi)
      client.println(convert_to_json("stoel", 1));
  }

  String line = client.readStringUntil('\r'); // --> Read line from server
  Serial.println(line); 

  Serial.println("TCP connection will be closed now!");
  client.stop();
}
