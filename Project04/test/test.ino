// #include <ESP8266WiFi.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_NeoMatrix.h>
// #include <Adafruit_NeoPixel.h>

// #define PIN 2
// #define ROWS 8
// #define COLUMNS 8

// const char* ssid      = "erwins";
// const char* password  = "1234567890";

// WiFiServer server(80);

// Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
//   NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
//   NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
//   NEO_GRB            + NEO_KHZ800);

// const uint16_t colors[] = {
//   matrix.Color(255, 0, 0), matrix.Color(0, 255 ,0), matrix.Color(0, 0, 255) };

// String header;
// int    i = 0;

// void setup() {
//   Serial.begin(9600);
//   // connectToWifi();
//   // startServer();
//   matrix.begin();
//   matrix.clear();
//   matrix.show();
//   Serial.println("Setup done");
//   delay(3000);
// }

// void  connectToWifi() {
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(5000);
//     Serial.print(":D ");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected.");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
// }

// void  startServer() {
//   server.begin();
//   Serial.println("Server started.");
// }

// void loop() {
//   clear_board();
//   matrix.setPixelColor(0, 255, 0, 0);
//   matrix.setPixelColor(1, 255, 0, 0);
//   matrix.show();
//   delay(500);
//   clear_board();
//   matrix.setPixelColor(2, 0, 255, 0);
//   matrix.setPixelColor(3, 0, 255, 0);
//   matrix.show();
//   delay(500);
//   clear_board();
//   matrix.setPixelColor(4, 0, 0, 255);
//   matrix.setPixelColor(5, 0, 0, 255);
//   matrix.show();
//   delay(500);
// }

// void clear_board() {
//   for (int i = 0; i < ROWS * COLUMNS; i++)
//     matrix.setPixelColor(i, 0, 0, 0);
// }


// #include <ESP8266WiFi.h>
// #include <FastLED.h>

// #define NUM_LEDS 64
// #define DATA_PIN 2
// CRGB leds[NUM_LEDS];

// void setup() {
//   pinMode(DATA_PIN, OUTPUT);
//   Serial.begin(9600);

//   FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
//   FastLED.setBrightness(50);
//   fill_solid(leds, NUM_LEDS, CRGB::Black);
//   leds[1] = CRGB::White;
//   leds[10] = CRGB::White;
//   leds[51] = CRGB::White;
//   FastLED.show();
//   Serial.print("let's goooo");
// }

// void  loop()
// {
//   return;
// }

#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define ROWS 8
#define COLUMNS 8

const char* ssid = "Stinky";
const char* password = "asdf56jkl";

WiFiServer server(80);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

String header;
bool ledStates[ROWS * COLUMNS] = {false}; // Track LED states
int     i = 0;
uint8_t r = 255;
uint8_t g = 0;
uint8_t b = 0;

void setup() {
  Serial.begin(115200);
  connectToWifi();
  startServer();
  matrix.begin();
  matrix.clear();
  matrix.show();
  matrix.setBrightness(25);
  Serial.println("Setup done");
}

void connectToWifi() {
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

void startServer() {
  server.begin();
  Serial.println("Server started.");
}

void loop() {
  faceTime();
  return ;
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        header = client.readStringUntil('\n');
        Serial.print("header: ");
        Serial.println(header);
        Serial.println("");
        if (header.startsWith("GET /led/")) {
          int ledIndex = extractLEDIndex(header);
          if (ledIndex >= 0) {
            toggleLED(ledIndex);
          }
          sendHTMLPage(client);
          break;
        }
      }
    }
    delay(1);
    client.stop();
  }
  updateLeds();
}

int extractLEDIndex(String line) {
  int startIndex = line.indexOf("GET /led/") + 9;
  int endIndex = line.indexOf(" ", startIndex);
  if (startIndex >= 0 && endIndex > startIndex)
    return line.substring(startIndex, endIndex).toInt();
  return -1;
}

void toggleLED(int button) {
  ledStates[button] = !ledStates[button]; // Toggle LED state
}

void updateLeds() {
  for (int i = 0; i < ROWS * COLUMNS; i++) {
    if (ledStates[i]) {
      matrix.setPixelColor(i, 255, 255, 255);
    } else {
      matrix.setPixelColor(i, 0, 0, 0);
    }
  }
  matrix.show();
}

void clear_board() {
  for (int i = 0; i < ROWS * COLUMNS; i++)
    matrix.setPixelColor(i, 0, 0, 0);
}

void sendHTMLPage(WiFiClient client) {
  header = "";
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println("<html><body>");
  client.println("<h1>Team 5 Project04</h1>");
  for (int i = 0; i < ROWS * COLUMNS; i++) {
    client.print("<a href=\"/led/");
    client.print(i);
    client.print("\" style=\"text-decoration:none; color:#000;\">");
    client.print("<button style=\"width:30px;height:30px; background-color:");
    if (ledStates[i]) {
      client.print("#00FF00"); // Highlight if LED is on
    } else {
      client.print("#FFFFFF");
    }
    client.print("\">");
    client.print("</button></a>");
    if ((i + 1) % COLUMNS == 0) {
      client.println("<br>");
    }
  }
  client.println("</body></html>");
}


void faceTime() {
  if (r && !g) {
    r -= 5;
    b += 5;
  }
  else if (b && !r) {
    b -= 5;
    g += 5;
  }
  else if (g && !b) {
    g -= 5;
    r += 5;
  }

  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print(b);
  Serial.println("");

  matrix.setPixelColor(2, r, g, b);
  matrix.setPixelColor(3, r, g, b);
  matrix.setPixelColor(4, r, g, b);
  matrix.setPixelColor(5, r, g, b);
  matrix.setPixelColor(9, r, g, b);
  matrix.setPixelColor(14, r, g, b);
  matrix.setPixelColor(16, r, g, b);
  matrix.setPixelColor(23, r, g, b);
  matrix.setPixelColor(24, r, g, b);
  matrix.setPixelColor(31, r, g, b);
  matrix.setPixelColor(32, r, g, b);
  matrix.setPixelColor(39, r, g, b);
  matrix.setPixelColor(40, r, g, b);
  matrix.setPixelColor(47, r, g, b);
  matrix.setPixelColor(49, r, g, b);
  matrix.setPixelColor(54, r, g, b);
  matrix.setPixelColor(58, r, g, b);
  matrix.setPixelColor(59, r, g, b);
  matrix.setPixelColor(60, r, g, b);
  matrix.setPixelColor(61, r, g, b);

  matrix.setPixelColor(26, r, g, b);
  matrix.setPixelColor(29, r, g, b);

  matrix.setPixelColor(42, r, g, b);
  matrix.setPixelColor(43, r, g, b);
  matrix.setPixelColor(44, r, g, b);
  matrix.setPixelColor(45, r, g, b);
  
  matrix.show();
  delay(20);
}
