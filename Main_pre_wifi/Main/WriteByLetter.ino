void WriteByLetter(String letters) {
  for (int i = 0; i < letters.length(); i++) {
    printLetter(letters.charAt(i));
    delay(500);
  }
}
