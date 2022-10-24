#include <Wire.h>
#include <ESP8266WiFi.h>


//ESP NODEMCU
// #define SDA_PIN 4
// #define SCL_PIN 5

//ESP01
#define SDA_PIN 2
#define SCL_PIN 0


const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x09;

const int shutterPin = 3;

boolean shutterState = 0;
boolean oldShutterState = 0;

int timeDelay = 0;

byte result = -1;
int startMillis = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN, I2C_SLAVE);
  Wire.onRequest(requestEvent);
  Wire.setClock(10000);

  randomSeed(analogRead(A0));
  timeDelay = random(10, 400);
  delay(timeDelay);

  pinMode(shutterPin, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(timeDelay);

}

void loop() {
  shutterState = digitalRead(shutterPin);
  
  if (shutterState && !oldShutterState) {
    startMillis = millis();
    result = scan("Testwerk");
    Serial.println(result);
    Serial.println(millis() - startMillis);
    
    oldShutterState = shutterState;
  }
  else {
    oldShutterState = shutterState;
  }



}


void requestEvent() {
  Wire.write(result);
  //Wire.write("hello\n"); // respond with message of 6 bytes
  // as expected by master
}


byte scan(String networkName) {
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t* bssid;
  int32_t channel;
  bool hidden;
  int scanResult;
  byte result = 0;

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0) {
    result = -2;
  } else if (scanResult > 0) {
    for (int8_t i = 0; i < scanResult; i++) {
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
      if (ssid == networkName) {
        //Serial.println(abs(rssi));
        result = abs(rssi);
      }
    }
  } else {
    result = -1;
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }

  return result;
}
