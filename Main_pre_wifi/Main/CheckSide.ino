// Function to check the current side of the MPU6050 sensor
uint8_t CheckSide() {
  mpu.getEvent(&a, &g, &temp);
  unsigned long check_time = millis();
  uint8_t side = 0;

  // Check if enough time has passed since the last side check
  if ((check_time - last_check_time) > 500) {

    // Read acceleration values
    float acc_x = a.acceleration.x;
    float acc_y = a.acceleration.y;

    // Determine the side based on acceleration values
    if (acc_x > 9) {
      side = 1;
    } else if (acc_y > 9) {
      side = 2;
    } else if (acc_x < -9) {
      side = 3;
    } else if (acc_y < -9) {
      side = 4;
    } else {
      side = 0;
    }

    // Update the last check time and last detected side
    last_check_time = check_time;
    last_side = side;
  } else {
    // If not enough time has passed, return the last detected side
    side = last_side;
  }

  // Uncomment the following line to print the current side to the serial monitor
  // Serial.println("Current Side: " + String(side));

  return side;
}
