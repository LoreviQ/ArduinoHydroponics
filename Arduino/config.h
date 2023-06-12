#include "env.h"

// ADD NEW SENSOR ID'S AS THEY'RE WIRED TO THE ARDUINO
char buffer[25];
char arduinoID[25] = "null"; 
char DHT1sensorID[25] = "null"; 
char DHT2sensorID[25] = "null"; 
char LDRsensorID[25] = "null";
char CO2sensorID[25] = "null";
char TBSensorID[25] = "null";
char *ids[] = {arduinoID, DHT1sensorID, DHT2sensorID, LDRsensorID, CO2sensorID, TBSensorID};//, TBSensorID};
const size_t numDevices = sizeof(ids) / sizeof(ids[0]);

// ADD A UNIQUE NAME FOR EACH SENSOR
const char arduino[] PROGMEM = {ARDUINO_NAME};
const char S1name[] PROGMEM = {"DHT22-Temp"};
const char S2name[] PROGMEM = {"DHT22-Hum"};
const char S3name[] PROGMEM = {"LDR"};
const char S4name[] PROGMEM = {"CO2"};
const char S5name[] PROGMEM = {"Turbidity"};
const char * const names[] PROGMEM = {arduino, S1name, S2name, S3name, S4name, S5name};

//LIST THE SENSOR TYPE (MATCHING WITH SERVER)
const char S1type[] PROGMEM = {"DHT22-T"};
const char S2type[] PROGMEM = {"DHT22-H"};
const char S3type[] PROGMEM = {"Grove Light Sensor"};
const char S4type[] PROGMEM = {"MH-Z19B CO2 Sensor"};
const char S5type[] PROGMEM = {"Turbidity Sensor"};
const char * const types[] PROGMEM = {S1type, S2type, S3type, S4type, S5type};