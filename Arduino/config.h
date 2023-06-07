#include "env.h"

// ADD NEW SENSOR ID'S AS THEY'RE WIRED TO THE ARDUINO
char arduinoID[25] = "null"; 
char DHT1sensorID[25] = "null"; 
char DHT2sensorID[25] = "null"; 
char LDRsensorID[25] = "null";
char CO2sensorID[25] = "null";
char *ids[] = {arduinoID, DHT1sensorID, DHT2sensorID, LDRsensorID, CO2sensorID};
const size_t numDevices = sizeof(ids) / sizeof(ids[0]);

// ADD A UNIQUE NAME FOR EACH SENSOR AND LIST IT'S TYPE (MATCHING WITH SERvER)
char *names[] = {ARDUINO_NAME, "DHT22-Temp", "DHT22-Hum", "LDR", "CO2"};
char *types[] = {"Arduino", "DHT22-T", "DHT22-H", "Grove Light Sensor", "MH-Z19B CO2 Sensor"};