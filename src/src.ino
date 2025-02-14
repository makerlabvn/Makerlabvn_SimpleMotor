#include "Makerlabvn_SimpleMotor.h"

Motor_lib motor_A;
Motor_lib motor_B;
TwoMotor_lib driver;

void setup() {
  motor_A.begin(6, 9, 8);
  motor_B.begin(5, 7, 4);
  driver.begin(&motor_A, &motor_B);
}

void loop() {
  driver.car_fw(50, 50);
  delay(1000);
  driver.car_stop();
  delay(1000);
  driver.car_bw(50, 50);
  delay(1000);
  driver.car_stop();
  delay(1000);
  driver.car_rotateL(50);
  delay(1000);
  driver.car_stop();
  delay(1000);
  driver.car_rotateR(50);
  delay(1000);
  driver.car_stop();
  delay(1000);
}