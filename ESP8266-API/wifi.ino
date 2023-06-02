// Defined in env.ino stored locally
String STASSID, STAPSK;
STASSID = getUsername();
STAPSK = getPassword();

void wifiConnect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(STASSID, STAPSK);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
}