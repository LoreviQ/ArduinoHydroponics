#ifndef APIHandler_h
#define APIHandler_h
#include "Arduino.h" 

class APIHandler {
  public:
    APIHandler(String serverName);
    String get(String endpoint);
    String post(String endpoint, String body);
  private:
    String _serverName;
};

#endif