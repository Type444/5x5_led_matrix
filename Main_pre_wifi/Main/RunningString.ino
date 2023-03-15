void RunningString(String temp_str, CHSV color) { 
  Serial.println("DEBUG: RunningString: " + String(temp_str)); // DEBUG
  uint16_t symbol = 0;
  int str_length = temp_str.length();  // str_length = 6
  uint16_t symbol_arr[5] = { 0b0, 0b0, 0b0, 0b0, 0b0 };
  // 0b 0000 0000 0000 0000
  // 0b 0000 0000 0000 0000
  // 0b 0000 0000 0000 0000
  // 0b 0000 0000 0000 0000
  // 0b 0000 0000 0000 0000
  
  int char_number = temp_str.charAt(0);  // int char_number(65) = [A]rivet

  if ((char_number > 64) && (char_number < 91)) {  // первая буква не идет в цикл
    for (int i = 0; i < 5; i++) {
      symbol = eng_alphabet[char_number - 65][i];  //000000 00000 01110
      symbol <<= 5;                                //000000 01110 00000
      symbol_arr[i] = symbol;
    }
    //symbol_arr at the end:
    //000000 01110 00000
    //000000 10001 00000
    //000000 11111 00000
    //000000 10001 00000
    //000000 10001 00000
  }

  for (int i = 0; i < 5; i++) {
    symbol_arr[i] <<= 1;  //сдвигаем каждый элемент на 1, ставим пробел
  }
  //000000 11100 00000
  //000001 00010 00000
  //000001 11110 00000
  //000001 00010 00000
  //000001 00010 00000


  for (int t = 1; t < str_length; t++) {
    char_number = temp_str.charAt(t);  // B=66(char_number)
    if ((char_number > 64) && (char_number < 91)) {
      for (int i = 0; i < 5; i++) {
        symbol = eng_alphabet[char_number - 65][i];  //11110
        symbol_arr[i] += symbol;
      }
      //symbol_arr at the end:
      //00000 0 11100 11110
      //00000 1 00010 10001
      //00000 1 11110 11110
      //00000 1 00010 10001
      //00000 1 00010 11110
      //сформировали 5х11 массив из двух букв
    }
    uint8_t draw_arr[5] = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000
    };
    // 0b000 00000
    // 0b000 00000
    // 0b000 00000
    // 0b000 00000
    // 0b000 00000
    for (int j = 0; j < 6; j++) {
      for (int k = 0; k < 5; k++) {  // формируем первые 5 бит в отдельный массив [01110] 11110
        draw_arr[k] = ((symbol_arr[k] >> 6) & 0xff);
      }
      // 0b000 01110
      // 0b000 10001
      // 0b000 11111
      // 0b000 10001
      // 0b000 10001
      draw(draw_arr, color);  //рисуем первые 5
      delay(70);
      for (int i = 0; i < 5; i++) {
        symbol_arr[i] <<= 1;  //сдвигаем каждый элемент на 1
        //000001 11001 11100
        //000010 00101 00010
        //000011 11101 11100
        //000010 00101 00010
        //000010 00101 11100
      }
    }
  }
}
