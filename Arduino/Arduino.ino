#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <serialStr.h>
#include <DHT.h>
#include <ErriezMHZ19B.h>
#include "config.h"
#include "env.h"

// Arduino/Sensor ID's/Names/Types listed in config.h
SoftwareSerial espSerial(12, 13); // TX, RX
serialStr strReader(&espSerial, '\n', 256);
bool initComplete = false;
int now = millis(), timer = millis();

// Setting up sensors
DHT dht (2, DHT22); // Setup DHT Sensor for pin 2
SoftwareSerial mhzSerial(4, 3); // TX, RX
ErriezMHZ19B mhz19b(&mhzSerial); // CO2 sensor connected to mhzSerial connection

void setup() {
  strReader.setCallback(espSerialHandler);
  Serial.begin(9600);
  espSerial.begin(74880);
  espSerial.println();
  dht.begin();
  while (!initComplete) {
    idle();
    now = millis();
    if (now - timer >= 2000) {
      // Initialization function
      // Has to be ran multiple times to set up all sensors while 'idle();' is reachable
      // Runs once every 2 seconds
      initializeArduino();
      timer = now;
    }
  }
}

// Main loop
// Collects data and sends to server
// Runs once every 30 seconds
void loop() {
  now = millis();
  idle();
  if (now - timer >= 30000) {
    Serial.println(F("Collecting Data"));
    collectData();
    timer = now;    
  }
}