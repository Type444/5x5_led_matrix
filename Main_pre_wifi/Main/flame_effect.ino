#define COOLING  55
#define SPARKING 120

byte heat[kMatrixHeight][kMatrixWidth];

void displayFlameEffect() {
  for (uint8_t x = 0; x < kMatrixWidth; x++) {
    // Step 1. Cool down every cell a little
    for (uint8_t y = 0; y < kMatrixHeight; y++) {
      heat[y][x] = qsub8(heat[y][x], random8(0, ((COOLING * 10) / kMatrixHeight) + 2));
    }

    // Step 2. Heat from each cell drifts 'up' and diffuses a little
    for (uint8_t y = kMatrixHeight - 1; y >= 2; y--) {
      heat[y][x] = (heat[y - 1][x] + heat[y - 2][x] + heat[y - 2][x]) / 3;
    }

    // Step 3. Randomly ignite new 'sparks' of heat near the bottom
    if (random8() < SPARKING) {
      int y = random8(2);
      heat[y][x] = qadd8(heat[y][x], random8(160, 255));
    }

    // Step 4. Map from heat cells to LED colors
    for (uint8_t y = 0; y < kMatrixHeight; y++) {
      byte colorindex = scale8(heat[y][x], 240);
      CRGB color = ColorFromPalette(HeatColors_p, colorindex);
      int pixelnumber;
      if (kMatrixSerpentineLayout == false) {
        pixelnumber = (y * kMatrixWidth) + x;
      } else {
        if (y & 0x01) {
          pixelnumber = (y * kMatrixWidth) + (kMatrixWidth - 1 - x);
        } else {
          pixelnumber = (y * kMatrixWidth) + x;
        }
      }
      leds[pixelnumber] = color;
    }
  }

  FastLED.show();
}
