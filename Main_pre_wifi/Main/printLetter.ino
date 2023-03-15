// Function to print a single letter on the LED matrix
void printLetter(char letter,CHSV color) {
  int char_number = letter;
  byte temp[5];

  // Iterate through each row of the LED matrix
  for (int i = 0; i < 5; i++) {
    // Check if the letter is an uppercase letter (A-Z)
    if ((char_number > 64) && (char_number < 91)) {
      temp[i] = eng_alphabet[char_number - 65][i];
    }
    // Check if the letter is a lowercase letter (a-z)
    else if ((char_number > 96) && (char_number < 123)) {
      temp[i] = eng_alphabet[char_number - 97][i];
    }
    // Check if the character is a space
    else if (char_number == 32) {
      temp[i] = eng_alphabet[28][i];
    }
    // If the character is not recognized, use a default character
    else {
      temp[i] = eng_alphabet[0][i];
    }
  }

  // Draw the letter on the LED matrix
  draw(temp, color);
}
