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

void analogWriteSetup(int pin) {}

#elif defined(ESP32)
#include <WiFi.h>      //ESP32 Core WiFi Library
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#define ESPWifiMulti WiFiMulti

static const int LEDC_CHANNEL_0 = 0;

void analogWrite(int pin, int value) {
  ledcAttachPin(pin, LEDC_CHANNEL_0);
  ledcWrite(LEDC_CHANNEL_0, value * 16);
}

void analogWriteSetup(int pin) {
  ledcSetup(LEDC_CHANNEL_0, 1000, 12);
}
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
  analogWriteSetup(LED_BUILTIN);
}

void loop() {
  // wait for WiFi connection
  if ((wifi_multi.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    if (http.begin(client, "http://breezy-hounds-sneeze-189-38-187-120.loca.lt/getLed")) {  // HTTP


      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          String possible_quote;
          Serial.println(payload);
          if (payload == "on") {
            pinMode(LED_BUILTIN, OUTPUT);
            digitalWrite(LED_BUILTIN, HIGH);
            possible_quote = "\"";
          } else if (payload == "off") {
            pinMode(LED_BUILTIN, OUTPUT);
            digitalWrite(LED_BUILTIN, LOW);
            possible_quote = "\"";
          } else {
            int power = payload.toInt();
            analogWrite(LED_BUILTIN, (255 * power) / 100);
            payload = String(power);
            possible_quote = "";
          }
          HTTPClient httpFeedback;
          httpFeedback.begin(client, "http://breezy-hounds-sneeze-189-38-187-120.loca.lt/setLedFeedback");
          httpFeedback.addHeader("Content-Type", "application/json");
          String led_feedback = String("{ \"led_state\": " + possible_quote + payload + possible_quote + " }");
          httpFeedback.POST(led_feedback);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(1000);
}
