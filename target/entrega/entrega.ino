/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>  //ESP8266 Core WiFi Library         
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#define ESPWifiMulti ESP8266WiFiMulti
#else
#include <WiFi.h>      //ESP32 Core WiFi Library
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#define ESPWifiMulti WiFiMulti
#endif

ESPWifiMulti wifi_multi;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  wifi_multi.addAP("Akine", "81133018");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // wait for WiFi connection
  if ((wifi_multi.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://breezy-hounds-sneeze-189-38-187-120.loca.lt/getLed")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          if (payload == "on") {
            digitalWrite(LED_BUILTIN, HIGH);
          } else if (payload == "off") {
            digitalWrite(LED_BUILTIN, LOW);
          }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}
