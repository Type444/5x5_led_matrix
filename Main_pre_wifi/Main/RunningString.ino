void RunningString(String temp_str, CHSV color) {
  temp_str = " " + temp_str + " ";
  Serial.println("DEBUG: RunningString: " + String(temp_str));
  uint16_t symbol = 0;
  int str_length = temp_str.length();
  uint16_t symbol_arr[5] = { 0b0, 0b0, 0b0, 0b0, 0b0 };

  int char_number = temp_str.charAt(0);

  if (((char_number > 64) && (char_number < 91)) || ((char_number > 96) && (char_number < 123))) {
    if (char_number > 96) char_number -= 32; // Convert lowercase to uppercase

    for (int i = 0; i < 5; i++) {
      symbol = eng_alphabet[char_number - 65][i];
      symbol <<= 5;
      symbol_arr[i] = symbol;
    }
  }

  for (int i = 0; i < 5; i++) {
    symbol_arr[i] <<= 1;
  }

  for (int t = 1; t < str_length; t++) {
    char_number = temp_str.charAt(t);
    if (((char_number > 64) && (char_number < 91)) || ((char_number > 96) && (char_number < 123))) {
      if (char_number > 96) char_number -= 32; // Convert lowercase to uppercase

      for (int i = 0; i < 5; i++) {
        symbol = eng_alphabet[char_number - 65][i];
        symbol_arr[i] += symbol;
      }
    }

    uint8_t draw_arr[5] = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000
    };

    for (int j = 0; j < 6; j++) {
      for (int k = 0; k < 5; k++) {
        draw_arr[k] = ((symbol_arr[k] >> 6) & 0xff);
      }
      draw(draw_arr, color);
      delay(70);
      for (int i = 0; i < 5; i++) {
        symbol_arr[i] <<= 1;
      }
    }
  }
}
