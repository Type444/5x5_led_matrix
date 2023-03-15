#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include "bitmap_characters.h"



Adafruit_MPU6050 mpu;

#define LED_PIN  13

#define COLOR_ORDER GRB
#define CHIPSET     WS2812B

#define BRIGHTNESS 64

sensors_event_t a, g, temp;
uint8_t last_side = 0;
unsigned long last_check_time = 0;

// Params for width and height
const uint8_t kMatrixWidth = 5;
const uint8_t kMatrixHeight = 5;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
const bool    kMatrixVertical = false;

const char* ssid = "Type444";
const char* password = "36aser762u";
ESP8266WebServer server(80);  // Create a server instance on port 80



String inputColor = "#FF0000";

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB * const leds( leds_plus_safety_pixel + 1);



void ChechkSide();
void DrawOneFrame();
void RunningString();
void WriteByLetter();
uint16_t XY();
void draw();
void printLetter();
void setupMPU();

String inputMessage = "";

void handleRoot() {
  String html = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                "<style>"
                "body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; }"
                "h1 { font-size: 24px; }"
                "form { display: inline-block; margin: 20px auto; background-color: #fff; padding: 20px; border-radius: 10px; }"
                "input[type='text'] { width: 100%; padding: 10px; font-size: 18px; border: 1px solid #ccc; border-radius: 5px; }"
                "input[type='color'] { width: 100%; padding: 10px; font-size: 18px; border: 1px solid #ccc; border-radius: 5px; }"
                "input[type='submit'] { display: block; width: 100%; padding: 10px; font-size: 18px; background-color: #008CBA; color: white; border: none; border-radius: 5px; margin-top: 10px; }"
                "input[type='submit']:hover { background-color: #0073aa; }"
                "</style>"
                "</head>"
                "<body>"
                "<h1>Enter Text to Display</h1>"
                "<form action='/submit' method='POST'>"
                "<input type='text' name='text' placeholder='Enter text'>"
                "<br><br>"
                "<input type='color' name='color' value='#FF0000'>"
                "<br><br>"
                "<input type='submit' value='Display Text'>"
                "</form>"
                "</body>"
                "</html>";
  server.send(200, "text/html", html);
}

CHSV hexToCHSV(String hexColor) {
  long rgb = strtol(&hexColor[1], NULL, 16);
  CRGB crgb((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
  CHSV chsv;
  chsv = rgb2hsv_approximate(crgb);
  return chsv;
}


void handleSubmit() {
  if (server.hasArg("text")) {
    inputMessage = server.arg("text");
    Serial.println("DEBUG: New input message received: " + inputMessage); // DEBUG
  }
  if (server.hasArg("color")) {
    inputColor = server.arg("color");
    Serial.println("DEBUG: New input color received: " + inputColor); // DEBUG
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);
  setupMPU();
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Configure server handlers
  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
  Serial.println("DEBUG: RunningString called with inputMessage: " + inputMessage); // DEBUG
  RunningString(inputMessage.c_str(), hexToCHSV(inputColor));
  delay(500);
}
