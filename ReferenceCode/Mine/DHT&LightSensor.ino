#include <DHT.h>
#include <math.h>

#define DHT_PIN 2
#define LIGHT_SENSOR_PIN 3

DHT dht (DHT_PIN, DHT22);

float humidity;
float temperature;
int lightValue;
float ResistanceLight;

void setup()
{
    Serial.begin(9600);
    dht.begin();
}

void loop()
{
  lightValue = analogRead(0);
  ResistanceLight=(1023-lightValue)*10/lightValue;
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.print("  |  ");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C ~ ");
  Serial.print("  |  ");
  Serial.print("Light: ");
  Serial.print("the analog read data is ");
  Serial.print(lightValue);
  Serial.print("the sensor resistance is ");
  Serial.println(ResistanceLight,DEC);

  delay(10000);
}

