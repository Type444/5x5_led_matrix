void printLetter(char letter) {
  int char_number = letter;
  byte temp[5];

  for (int i = 0; i < 5; i++) {
    if ((char_number > 64) && (char_number < 91)) {
      temp[i] = eng_alphabet[char_number - 65][i];
    } else if ((char_number > 96) && (char_number < 123)) {
      temp[i] = eng_alphabet[char_number - 97][i];
    } else if (char_number == 32) {
      temp[i] = eng_alphabet[28][i];
    } else {
      temp[i] = eng_alphabet[0][i];
    }
  }
  
  draw(temp);
}
