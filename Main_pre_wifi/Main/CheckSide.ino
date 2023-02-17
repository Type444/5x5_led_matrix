uint8_t CheckSide() {
  mpu.getEvent(&a, &g, &temp);
  unsigned long check_time = millis();
  uint8_t side = 0;

  if ((check_time - last_check_time) > 500) {
    float acc_x = a.acceleration.x;
    float acc_y = a.acceleration.y;
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
    last_check_time = check_time;
    last_side = side;
  } else {
    side = last_side;
  }
  //Serial.println("Curent Side: " + String(side));
  return side;
}
