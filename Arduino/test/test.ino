String username, password;

void setup()
{
    Serial.begin(9600);
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