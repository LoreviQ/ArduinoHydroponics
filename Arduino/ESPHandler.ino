void espSerialHandler(const char* inStr) {
  Serial.print("From ESP: ");
  Serial.println(inStr);

  if (!initComplete) {
    if (strncmp(inStr, "ID: ", 3) == 0) {
      for (int i=0; i<4; i++) {
        if (strcmp(ids[i], "null") == 0){ 
          memcpy(ids[i], &inStr[5], 24);
          break;
        }
      }
    };
  }
}

void sendToESP(StaticJsonDocument<256> JSONrequest) {
  char request[256];
  serializeJson(JSONrequest, request);
  Serial.print("Sending JSON: ");
  Serial.println(request);
  espSerial.println(request);
}