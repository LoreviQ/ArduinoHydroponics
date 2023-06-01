#define LOCAL "localString"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.println(LOCAL);
    Serial.println(GLOBAL);
}