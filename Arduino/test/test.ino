String username;
String password;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    delay(1000);
    printFunc();
    username = getUsername();
    password = getPassword();
    Serial.println(username);
    Serial.println(password);
}