#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMP_SENSOR_PIN 2

OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature sensors(&oneWire);

float temperature;

void setup()
{
    Serial.begin(9600);
    sensors.begin();
}

void loop()
{
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C ~ ");

    delay(5000);
}