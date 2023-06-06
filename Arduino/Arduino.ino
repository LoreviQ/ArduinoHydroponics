#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <serialStr.h>
#include <DHT.h>
#include "env.h"

SoftwareSerial espSerial(12, 13); // TX, RX
SoftwareSerial CO2Serial(4, 3); // TX, RX
serialStr strReader(&espSerial, '\n', 256);
int now = millis(), timer = millis();
bool initComplete = false;
char arduinoID[25] = "null"; 
char DHT1sensorID[25] = "null"; 
char DHT2sensorID[25] = "null"; 
char LDRsensorID[25] = "null";
char *ids[] = {arduinoID, DHT1sensorID, DHT2sensorID, LDRsensorID};
char *names[] = {ARDUINO_NAME, "DHT22-Temp", "DHT22-Hum", "LDR"};
char *types[] = {"Arduino", "DHT22", "DHT22", "LDR"};
char *variables[] = {"null", "Temperature", "Humidity", "Resistance"};
char *units[] = {"null", "Centigrade", "Percent", "Ohms"};
const size_t numDevices = sizeof(ids) / sizeof(ids[0]);

DHT dht (2, DHT22); // Setup DHT Sensor for pin 2

void setup() {
  strReader.setCallback(espSerialHandler);
  Serial.begin(9600);
  espSerial.begin(74880);
  espSerial.println();
  dht.begin();
}

void loop() {
  now = millis();
  idle();
  if (!initComplete) {
    if (now - timer >= 2000) {
      initializeArduino();
      timer = now;
    }
  } else {
    if (now - timer >= 30000) {
      collectData();
      timer = now;    
    }
  }
}