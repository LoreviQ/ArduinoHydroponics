void espSerialHandler(const char* inStr) {
  Serial.println(String("From ESP: ") + inStr);
}