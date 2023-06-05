#include <DHT.h>;

#define DHTPIN1 2

DHT dht (DHTPIN1, DHT22);

float humidity;
float temperature;

void setup()
{
    Serial.begin(9600);
    dht.begin();
}

void loop()
{
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%");
    Serial.print("  |  ");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C ~ ");
    delay(5000);
}
