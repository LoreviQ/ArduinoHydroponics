#include<SoftwareSerial.h>
#include <DHT.h>
#include <math.h>

// Defining pins
#define DHT_PIN 2
#define LIGHT_SENSOR_PIN 3
SoftwareSerial comm(12, 13); //setting Tx and Rx pins

// Creating variables
String ssid = "";
String password = "";
boolean No_IP = false; //variable to check for ip Address
String server; //variable for sending data to webpage
String IP; //variable to store ip Address
float humidity;
float temperature;
int lightValue;
float lightRes;
DHT dht (DHT_PIN, DHT22);

// Website
String webdata;

void setup() {
  Serial.begin(9600);
  comm.begin(9600);
  dht.begin();
  if (!wifi_init()) {stop();};
  Serial.println("System Ready..");
}

void loop() {
  Serial.println("Refresh Page");
  for (int i = 0; i < 1000; i++) {
    while (comm.available()) {
      if (comm.find("0,CONNECT")) {
        Serial.println("Collecting Data");
        readSensors();
        Serial.println("Sending Data");
        sendToServer();
        Serial.println("Finished");
        delay(1000);
      }
    }
    delay(1);
  }
}

//check for the availability of IP Address
void findIp(int time1) { 
  int time2 = millis();
  while (time2 + time1 > millis()) {
    while (comm.available() > 0) {
      if (comm.find("IP has been read")) {
        No_IP = true;
      }
    }
  }
}

//Display the IP Address
void showIP() { 
  IP = "";
  char ch = 0;
  while (1) {
    comm.println("AT+CIFSR");
    while (comm.available() > 0) {
      if (comm.find("STAIP,")) {
        delay(1000);
        Serial.print("IP Address:");
        while (comm.available() > 0) {
          ch = comm.read();
          if (ch == '+') {
            break;
          }
          IP += ch;
        }
      }
      if (ch == '+') {
        break;
      }
    }
    if (ch == '+') {
      break;
    }
    delay(1000);
  }
  Serial.print(IP);
  Serial.print("Port:");
  Serial.println(80);
}

//Define the process for sending AT commands to module
int establishConnection(String command, int timeOut) { 
  for (int i = 0; i < 5; i++) {
    Serial.println(command);
    comm.println(command);
    while (comm.available()) {
      if (comm.find("OK")) {
        Serial.println("OK");
        return 1;
      }
    }
    delay(timeOut);
  }
  Serial.println("Error");
  return 0;
}

//send AT commands to module
int wifi_init() { 
  if (!establishConnection("AT", 100)) {
    Serial.println("Error connecting to ESP-01S");
    return 0;
  };
  delay(1000);
  establishConnection("AT+CWMODE=3", 100);
  delay(1000);
  establishConnection("AT+CWQAP", 100);
  delay(1000);
  establishConnection("AT+RST", 5000);
  delay(1000);
  findIp(5000);
  if (!No_IP) {
    Serial.println("Connecting Wifi....");
    establishConnection(String("AT+CWJAP=\"") + ssid + String("\",\"") + password + String("\""), 7000);
  } else {}
  Serial.println("Wifi Connected");
  showIP();
  establishConnection("AT+CIPMUX=1", 100);
  establishConnection("AT+CIPSERVER=1,80", 100);
  return 1;
}

//send data to module
void sendData(String data) { 
  int p = 0;
  while (1) {
    unsigned int dataLen = data.length();
    Serial.print("AT+CIPSEND=0,");
    comm.print("AT+CIPSEND=0,");
    Serial.println(dataLen + 2);
    comm.println(dataLen + 2);
    delay(100);
    Serial.println(data);
    comm.println(data);
    while (comm.available()) {
      //Serial.print(Serial.read());
      if (comm.find("OK")) {
        p = 11;
        break;
      }
    }
    if (p == 11) {
      break;
    }
    delay(100);
  }
}

//send data to webpage 
void sendToServer() { 
  webdata =
    String("<p>I am Arduino</p>") +
    String("<p>Data Received Successfully.....</p>") + 
    String("<p>The Humidity is: ") + String(humidity) + String("%</p>") +
    String("<p>The Temperature is: ") + String(temperature) + String("°C</p>") +
    String("<p>The Light Value (Analog Read) is: ") + String(lightValue) + String("</p>") +
    String("<p>The Light Sensor Resistance is: ") + String(lightRes) + String("Ω</p>");
  sendData(webdata);
  delay(5000);
  comm.println("AT+CIPCLOSE=0");
}

//reads sensor data
void readSensors() {
  lightValue = analogRead(0);
  lightRes=(1023-lightValue)*10/lightValue;
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  delay(5000);
}

// stops execution on failstate
void stop() {
  Serial.println("Code Execution Stopped");
  while(1);
}
