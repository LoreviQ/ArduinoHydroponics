#include <SoftwareSerial.h>
#include <ErriezMHZ19B.h>

SoftwareSerial mhzSerial(4, 3); // TX, RX
ErriezMHZ19B mhz19b(&mhzSerial);

void setup()
{
    char firmwareVersion[5];

    // Initialize serial port to print diagnostics and CO2 output
    Serial.begin(9600);
    Serial.println(F("\nErriez MH-Z19B CO2 Sensor example"));

    // Initialize senor software serial at fixed 9600 baudrate
    mhzSerial.begin(9600);

    // Optional: Detect MH-Z19B sensor (check wiring / power)
    while ( !mhz19b.detect() ) {
        Serial.println(F("Detecting MH-Z19B sensor..."));
        delay(2000);
    };

    // Sensor requires 3 minutes warming-up after power-on
    while (mhz19b.isWarmingUp()) {
        Serial.println(F("Warming up..."));
        delay(2000);
    };

    // Optional: Print firmware version
    Serial.print(F("  Firmware: "));
    mhz19b.getVersion(firmwareVersion, sizeof(firmwareVersion));
    Serial.println(firmwareVersion);

    // Optional: Set CO2 range 2000ppm or 5000ppm (default) once
    // Serial.print(F("Set range..."));
    // mhz19b.setRange2000ppm();
    // mhz19b.setRange5000ppm();

    // Optional: Print operating range
    Serial.print(F("  Range: "));
    Serial.print(mhz19b.getRange());
    Serial.println(F("ppm"));

    // Optional: Set automatic calibration on (true) or off (false) once
    // Serial.print(F("Set auto calibrate..."));
    // mhz19b.setAutoCalibration(true);

    // Optional: Print Automatic Baseline Calibration status
    Serial.print(F("  Auto calibrate: "));
    Serial.println(mhz19b.getAutoCalibration() ? F("On") : F("Off"));
}

void loop()
{
    int16_t result;

    // Minimum interval between CO2 reads is required
    if (mhz19b.isReady()) {
        // Read CO2 concentration from sensor
        result = mhz19b.readCO2();

        // Print result
        if (result < 0) {
            // An error occurred
            printErrorCode(result);
        } else {
            // Print CO2 concentration in ppm
            Serial.print(result);
            Serial.println(F(" ppm"));
        }
    }
}


void printErrorCode(int16_t result)
{
    // Print error code
    switch (result) {
        case MHZ19B_RESULT_ERR_CRC:
            Serial.println(F("CRC error"));
            break;
        case MHZ19B_RESULT_ERR_TIMEOUT:
            Serial.println(F("RX timeout"));
            break;
        default:
            Serial.print(F("Error: "));
            Serial.println(result);
            break;
    }
}