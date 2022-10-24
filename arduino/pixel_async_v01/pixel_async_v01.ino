#include <Wire.h>
#include <ESP8266WiFi.h>


//ESP NODEMCU
// #define SDA_PIN 4
// #define SCL_PIN 5

//ESP01
#define SDA_PIN 2
#define SCL_PIN 0


const int16_t I2C_MASTER = 128;
const int16_t I2C_SLAVE = 4;

const int shutterPin = 3;

boolean shutterState = 0;
boolean oldShutterState = 0;

int timeDelay = 0;


int scanStartMillis = 0;
int scanEndMillis = 0;
int scanTime = 0;
byte scanRssi = 0;

boolean scanDone = true;

String networkName = "Testwerk";

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


  // WiFi.scanNetworks(/*async=*/true, /*hidden=*/true);

}
void loop() {
  if (scanDone) {
    scanAsync();
  }

}


void requestEvent() {
  int scanAge = millis() - scanEndMillis;
  Wire.write(scanRssi);
  // Wire.write(scanAge);
  // Wire.write("hello"); // respond with message of 6 bytes
  // as expected by master
}


void scanAsync() {
  //Serial.println("Start Scan...");
  scanStartMillis = millis();
  WiFi.scanNetworksAsync(processScanResult, true);
  scanDone = false;

}

void processScanResult(int networksFound)
{
  scanEndMillis = millis();
  //Serial.printf("%d network(s) found\n", networksFound);
  for (int i = 0; i < networksFound; i++)
  {
    if (WiFi.SSID(i) == networkName) {
      scanRssi = abs(WiFi.RSSI(i));
      scanTime = millis() - scanStartMillis;
    }
    //Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
  }
  //Serial.println("Start Done...");
  //Serial.print("Scan time: ");
  //Serial.println(scanTime);
  //Serial.print("Scan RSSI: ");
  //Serial.println(scanRssi);
  //Serial.println();
  scanDone = true;
}
