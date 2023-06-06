#include <SoftwareSerial.h>

SoftwareSerial CO2Serial(4, 3); // TX, RX
int now = millis(), timer = millis();
byte message[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

void setup() {
  Serial.begin(9600);
  CO2Serial.begin(9600);
}

void loop() {
  now = millis();

  if (Serial.available() > 0) {
    int incomingByte = CO2Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  if (now - timer >= 5000) {
    CO2Serial.write(message, sizeof(message));
    timer = now;
  }
}