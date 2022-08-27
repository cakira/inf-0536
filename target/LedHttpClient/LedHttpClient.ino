/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

#define SERVER_IP "192.168.15.11:3000"

//#ifndef STASSID
#define STASSID "CantinhoJC"
#define STAPSK  "#lutero1517"
//#endif

void setup() {
  
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  // wait for WiFi connection
  String payload;
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://192.168.15.11:3000/getLed")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          payload = http.getString();
          
          
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  //delay(1000);
  if(payload.equals("1")) {
    Serial.println("Entrou no equals yes");
    digitalWrite(LED_BUILTIN, 0);
    digitalWrite(5, HIGH);
  } else {
    Serial.println("Entrou no equals no");
    digitalWrite(LED_BUILTIN, 1);
    digitalWrite(5, LOW);
  }
  
  /*
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  */
  delay(10000);
}
