#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define ROWS 8
#define COLUMNS 8
#define LED_COUNT 64

const char* ssid = "Stinky";
const char* password = "asdf56jkl";

WiFiServer server(80);
String     header;
int        LEDState[LED_COUNT];

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setBrightness(50);
  matrix.clear();
  matrix.show();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  clear_board();
}

void loop() {

  WiFiClient client = server.available();

  if (client) 
  {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) 
    { 
      if (client.available()) {
        currentLine = client.readStringUntil('\n');
        // if (currentLine.startsWith("GET /")) {
        //   sendHTMLPage(client);
        //   break;
        // }
      if (currentLine.startsWith("GET /led/")) {
          int ledIndex = extractLEDIndex(currentLine);
          if (ledIndex >= 0) {
            toggleLED(ledIndex);
          }
          sendHTMLPage(client);
          break;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void updateMatrix() {
  matrix.clear();
  for (int i = 0; i < LED_COUNT; i++) {
    if (LEDState[i] == 1)
      matrix.setPixelColor(i, matrix.Color(255, 255, 255));
    else
      matrix.setPixelColor(i, matrix.Color(0, 0, 0));
  }
  matrix.show();
}

void toggleLED(int index) {
  Serial.println(index);
  if (index >= 0 && index < LED_COUNT) {
    LEDState[index] = 1 - LEDState[index];
    updateMatrix();
  }
  Serial.print(" ");
}

int extractLEDIndex(String line) {
  int startIndex = line.indexOf("GET /led/") + 9;
  int endIndex = line.indexOf(" ", startIndex);
  if (startIndex >= 0 && endIndex > startIndex)
    return line.substring(startIndex, endIndex).toInt();
  return -1; // Return -1 if extraction fails
}

void clear_board() {
  for (int i = 0; i < ROWS * COLUMNS; i++)
    matrix.setPixelColor(i, 0, 0, 0);
  matrix.show();
}

void sendHTMLPage(WiFiClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset=\"UTF-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<style>");
  client.println(".grid-container { display: grid; grid-template-columns: repeat(8, 1fr); gap: 10px; margin: 20px; width: 400px; }");
  client.println(".grid-button { width: 50px; height: 50px; background-color: #ccc; border: none; cursor: pointer; }");
  client.println("</style>");
  client.println("<title>Button Grid</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div class=\"grid-container\" id=\"grid\">");
  for (int i = 0; i < LED_COUNT; i++) {
    client.print("<button class=\"grid-button\" id=\"button-");
    client.print(i);
    client.print("\" onclick=\"toggleLED(");
    client.print(i);
    client.println(")\"></button>");
  }
  client.println("</div>");
  client.println("<script>");
  client.println("function toggleLED(index) {");
  client.println("  var button = document.getElementById('button-' + index);");
  client.println("  if (button.style.backgroundColor === 'red') {");
  client.println("    button.style.backgroundColor = '#ccc';");
  client.println("  } else {");
  client.println("    button.style.backgroundColor = 'red';");
  client.println("  }");
  client.println("  fetch('/led/' + index);");
  client.println("}");
  client.println("</script>");
  client.println("</body>");
  client.println("</html>");
}
