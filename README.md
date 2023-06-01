# ArduinoHydroponics

Project for the Arduino automation for Hydroponics system

Circuit diagram updated here: https://wokwi.com/projects/363882811430949889

Code is split into 3 parts in approropiately named directories:

-   Arduino code which collects sensor data, directs actuators and interfaces with the ESP8266 Chip
-   ESP8266 code which interfaces with the Arduino and communicates with the server via HTTP requests
-   Server based code which consists of a Node.js app that listens to HTTP requests and interfaces with the database accordingly
