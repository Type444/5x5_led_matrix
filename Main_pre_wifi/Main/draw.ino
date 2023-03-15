// Function to draw the text based on the orientation determined by CheckSide()
void draw(uint8_t temp_array[5], CHSV color) {
  int side = CheckSide();

  // Iterate through each pixel in the LED matrix
  for (uint8_t x = 0; x < kMatrixWidth; x++) {
    for (uint8_t y = 0; y < kMatrixHeight; y++) {
      uint8_t temp_x = x;
      uint8_t temp_y = y;

      // Determine the orientation based on the value of 'side'
      if (side == 2) {
        temp_x = 4 - y;
        temp_y = x;
      } else if (side == 4) {
        temp_x = y;
        temp_y = 4 - x;
      } else if (side == 1) {
        temp_x = 4 - x;
        temp_y = 4 - y;
      } else if (side == 3) {
        temp_x = x;
        temp_y = y;
      }

      // Set the LED color based on the bit value in temp_array
      if (bitRead(temp_array[temp_y], temp_x)) {
        leds[XY(x, y)] = color;
      } else {
        leds[XY(x, y)] = CHSV(0, 0, 0);
      }
    }
  }

  // Display the updated LED matrix
  FastLED.show();
}
