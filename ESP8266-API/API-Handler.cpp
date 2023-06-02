#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "Arduino.h"
#include "API-Handler.h"

APIHandler::APIHandler(String serverName) {
  _serverName = serverName;
}

String APIHandler::get(String endpoint) {
  if(WiFi.status()== WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String serverPath = _serverName + endpoint;
    http.begin(client, serverPath.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      return payload;
    } else {
      String response = String("Error code: ") + String(httpResponseCode);
      return response;
    }
    http.end();
  } else {
    return String("WiFi Disconnected");
  }
}

String APIHandler::post(String endpoint, String body) {
  if(WiFi.status()== WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String serverPath = _serverName + endpoint;
    http.begin(client, serverPath.c_str());
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(body);
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      return payload;
    } else {
      String response = String("Error code: ") + String(httpResponseCode);
      return response;
    }
    http.end();
  } else {
    return String("WiFi Disconnected");
  }
}