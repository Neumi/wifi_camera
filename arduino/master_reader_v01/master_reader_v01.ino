
#include <Wire.h>
#include <PolledTimeout.h>


// nodemcu
#define SDA_PIN 4
#define SCL_PIN 5
const int16_t I2C_MASTER = 128;

const int deviceCount = 16;

void setup() {
  Serial.begin(115200);  // start serial for output
  Wire.begin(SDA_PIN, SCL_PIN, I2C_MASTER);        // join i2c bus (address optional for master)
  Wire.setClock(10000);

}

boolean initialize = true;
void loop() {
  using periodic = esp8266::polledTimeout::periodicMs;
  static periodic nextPing(500);

  if (nextPing) {
    for (int deviceAddress = 1; deviceAddress < deviceCount + 1; deviceAddress++)
    {
      Wire.requestFrom(deviceAddress, 1);
      while (Wire.available()) { // slave may send less than requested
        byte rssi = Wire.read(); // receive a byte as character
        //Serial.print("RSSI: ");
        Serial.print(rssi);         // print the rssi
        Serial.print(",");
      }
    }
    Serial.println();
  }

  /*
    if (nextPing) {
    Wire.requestFrom(I2C_SLAVE, 1);    // request 6 bytes from slave device #8

    while (Wire.available()) { // slave may send less than requested
      byte rssi = Wire.read(); // receive a byte as character
      Serial.print(rssi);         // print the rssi
    }
    Serial.println();
    }
  */
}
