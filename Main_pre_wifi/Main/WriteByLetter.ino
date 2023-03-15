void WriteByLetter(String letters, CHSV color) {
  Serial.println("DEBUG: WriteByLetter: " + letters); // DEBUG
  for (int i = 0; i < letters.length(); i++) {
    printLetter(letters.charAt(i), color);
    delay(500);
  }
}
