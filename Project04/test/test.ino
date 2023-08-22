#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
 #define PSTR
#endif

#define PIN 6

const char* ssid      = "Stinky";
const char* password  = "asdf56jkl";

WiFiServer server(80);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(6, 6, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

String header;

void setup() {
  Serial.begin(9600);
  connectToWifi();
  startServer();
  matrix.begin();
  Serial.println("Setup done");
}

void  connectToWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(":D ");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void  startServer() {
  server.begin();
  Serial.println("Server started.");
}

void loop() {
  Serial.println("looping");
  delay(5000);
}
