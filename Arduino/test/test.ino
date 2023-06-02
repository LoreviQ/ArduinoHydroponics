#include "env.h"

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    delay(1000);
    Serial.println(SSID);
    Serial.println(PASSWORD);
}