#include <FastLED.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


Adafruit_MPU6050 mpu;

#define LED_PIN  16

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

byte eng_alphabet[29][5] = {{
    0b01110,
    0b10001,
    0b11111,
    0b10001,
    0b10001
  }, {
    0b11110,
    0b10001,
    0b11110,
    0b10001,
    0b11110
  }, {
    0b01110,
    0b10000,
    0b10000,
    0b10000,
    0b01110
  }, {
    0b11110,
    0b10001,
    0b10001,
    0b10001,
    0b11110
  }, {
    0b11111,
    0b10000,
    0b11111,
    0b10000,
    0b11111
  }, {
    0b11111,
    0b10000,
    0b11110,
    0b10000,
    0b10000
  }, {
    0b11111,
    0b10000,
    0b10011,
    0b10001,
    0b11111
  }, {
    0b10001,
    0b10001,
    0b11111,
    0b10001,
    0b10001
  }, {
    0b01110,
    0b00100,
    0b00100,
    0b00100,
    0b01110
  }, {
    0b00100,
    0b00100,
    0b00100,
    0b10100,
    0b11100
  }, {
    0b10010,
    0b10100,
    0b11000,
    0b10100,
    0b10010
  }, {
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b11110
  }, {
    0b10001,
    0b11011,
    0b10101,
    0b10001,
    0b10001
  }, {
    0b10001,
    0b11001,
    0b10101,
    0b10011,
    0b10001
  }, {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b01110
  }, {
    0b11110,
    0b10001,
    0b11110,
    0b10000,
    0b10000
  }, {
    0b11110,
    0b10010,
    0b10010,
    0b11110,
    0b00001
  }, {
    0b11110,
    0b10001,
    0b11110,
    0b10100,
    0b10010
  }, {
    0b01111,
    0b10000,
    0b01110,
    0b00001,
    0b11110
  }, {
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100
  }, {
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b01110
  }, {
    0b10001,
    0b10001,
    0b10001,
    0b01010,
    0b00100
  }, {
    0b10101,
    0b10101,
    0b10101,
    0b10101,
    0b01010
  }, {
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001
  }, {
    0b10001,
    0b01010,
    0b00100,
    0b00100,
    0b00100
  }, {
    0b11111,
    0b00010,
    0b00100,
    0b01000,
    0b11111
  }, {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
  }
};

byte smile[5] = {
  0b01010,
  0b01010,
  0b00000,
  0b10001,
  0b01110
};

byte shoop_da_whoop[5] = {
  0b10001,
  0b00000,
  0b11111,
  0b10001,
  0b11111
};

byte space[5] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

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

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);
  setupMPU();
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
}

void loop()
{
  uint32_t ms = millis();
  if ( ms < 5000 ) {
    FastLED.setBrightness( scale8( BRIGHTNESS, (ms * 256) / 5000));
  } else {
    FastLED.setBrightness(BRIGHTNESS);
  }


  //printLetter('D');
  //printLetter('F');
  RunningString(" MOM AND DAD I LOVE YOU  ");
  draw(shoop_da_whoop);
  delay(1000);

}
