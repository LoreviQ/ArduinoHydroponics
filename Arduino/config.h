#include "env.h"

// ADD NEW SENSOR ID'S AS THEY'RE WIRED TO THE ARDUINO
char buffer[25];
char arduinoID[25] = "null"; 
char DHTT1sensorID[25] = "null";
char DHTH1sensorID[25] = "null"; 
char DHTT2sensorID[25] = "null";
char DHTH2sensorID[25] = "null";
char LDR1sensorID[25] = "null";
char LDR2sensorID[25] = "null";
char CO21sensorID[25] = "null";
char CO22sensorID[25] = "null";
char *ids[] = {arduinoID, DHTT1sensorID, DHTH1sensorID, DHTT2sensorID, DHTH2sensorID, LDR1sensorID, LDR2sensorID, CO21sensorID, CO22sensorID};//, TBSensorID};
const size_t numDevices = sizeof(ids) / sizeof(ids[0]);

// ADD A UNIQUE NAME FOR EACH SENSOR
const char arduino[] PROGMEM = {ARDUINO_NAME};
const char S1name[] PROGMEM = {"DHT22-Temp-1"};
const char S2name[] PROGMEM = {"DHT22-Hum-1"};
const char S3name[] PROGMEM = {"DHT22-Temp-2"};
const char S4name[] PROGMEM = {"DHT22-Hum-2"};
const char S5name[] PROGMEM = {"LDR-1"};
const char S6name[] PROGMEM = {"LDR-2"};
const char S7name[] PROGMEM = {"CO2-1"};
const char S8name[] PROGMEM = {"CO2-2"};
const char * const names[] PROGMEM = {arduino, S1name, S2name, S3name, S4name, S5name, S6name, S7name, S8name};

//LIST THE SENSOR TYPE (MATCHING WITH SERVER)
const char S1type[] PROGMEM = {"DHT22-T"};
const char S2type[] PROGMEM = {"DHT22-H"};
const char S3type[] PROGMEM = {"DHT22-T"};
const char S4type[] PROGMEM = {"DHT22-H"};
const char S5type[] PROGMEM = {"Grove Light Sensor"};
const char S6type[] PROGMEM = {"Grove Light Sensor"};
const char S7type[] PROGMEM = {"MH-Z19B CO2 Sensor"};
const char S8type[] PROGMEM = {"MH-Z19B CO2 Sensor"};
const char * const types[] PROGMEM = {S1type, S2type, S3type, S4type, S5type, S6type, S7type, S8type};