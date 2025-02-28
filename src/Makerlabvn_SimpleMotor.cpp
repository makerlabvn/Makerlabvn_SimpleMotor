#include "Arduino.h"
/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Makerlabvn_SimpleMotor.h"

/* ------------------------------------------------------------------------- */
/*                                  HÀM TẠO                                  */
/* ------------------------------------------------------------------------- */
Makerlabvn_SimpleMotor::Makerlabvn_SimpleMotor() {}
Makerlabvn_SimpleMotor::Makerlabvn_SimpleMotor(
    int pinIn1, int pinIn2,
    int pinIn3, int pinIn4)
{
  _pinIn1 = pinIn1;
  _pinIn2 = pinIn2; // ~PWM
  _pinIn3 = pinIn3; // ~PWM
  _pinIn4 = pinIn4;

  pinMode(_pinIn1, OUTPUT);
  pinMode(_pinIn2, OUTPUT);
  pinMode(_pinIn3, OUTPUT);
  pinMode(_pinIn4, OUTPUT);

  digitalWrite(_pinIn1, LOW);
  digitalWrite(_pinIn2, LOW);
  digitalWrite(_pinIn3, LOW);
  digitalWrite(_pinIn4, LOW);
}

/* ------------------------------------------------------------------------- */
/*                            HÀM ĐIỀU KHIỂN MOTOR                           */
/* ------------------------------------------------------------------------- */

/**
 * Điều khiển motor kênh A quay thuận
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void Makerlabvn_SimpleMotor::motorA_fw(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  // Điều khiển Motor bên TRÁI quay tới
  digitalWrite(_pinIn1, LOW);
  analogWrite(_pinIn2, speed); // ~PWM
}

/**
 * Điều khiển motor kênh B quay thuận
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void Makerlabvn_SimpleMotor::motorB_fw(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  // Điều khiển Motor bên PHẢI quay tới
  digitalWrite(_pinIn4, LOW);
  analogWrite(_pinIn3, speed); // ~PWM
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển motor kênh A quay ngược
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void Makerlabvn_SimpleMotor::motorA_bw(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  // Điều khiển Motor bên TRÁI quay lùi
  digitalWrite(_pinIn1, HIGH);
  analogWrite(_pinIn2, 255 - speed); // ~PWM
}

/**
 * Điều khiển motor kênh B quay ngược
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void Makerlabvn_SimpleMotor::motorB_bw(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  // Điều khiển Motor bên PHẢI quay lùi
  digitalWrite(_pinIn4, HIGH);
  analogWrite(_pinIn3, 255 - speed); // ~PWM
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển motor kênh A dừng lại
 */
void Makerlabvn_SimpleMotor::motorA_stop()
{
  // Điều khiển Motor bên TRÁI dừng lại
  digitalWrite(_pinIn1, LOW);
  digitalWrite(_pinIn2, LOW); // none ~PWM
}

/**
 * Điều khiển motor kênh B dừng lại
 */
void Makerlabvn_SimpleMotor::motorB_stop()
{
  // Điều khiển Motor bên PHẢI dừng lại
  digitalWrite(_pinIn4, LOW);
  digitalWrite(_pinIn3, LOW); // none ~PWM
}

/* ------------------------------------------------------------------------- */
/*                             HÀM ĐIỀU KHIỂN XE                             */
/* ------------------------------------------------------------------------- */

/**
 * Điều khiển xe đi tới
 *
 * - speedA : tốc độ động cơ kênh A, bên TRÁI của xe
 *            phạm vi giá trị từ 0% đến 100%
 *
 * - speedB : tốc độ động cơ kênh B, bên PHẢI của xe
 *            phạm vi giá trị từ 0% đến 100%
 */
void Makerlabvn_SimpleMotor::car_fw(int speedA, int speedB)
{
  // Xử lý giá trị tốc độ nhận được
  speedA = calculate_speed(speedA);
  speedB = calculate_speed(speedB);

  motorA_fw(speedA); // Điều khiển motor kênh A quay thuận
  motorB_fw(speedB); // Điều khiển motor kênh B quay thuận
}

/**
 * Điều khiển xe đi lùi
 *
 * - speedA : tốc độ động cơ kênh A, bên TRÁI của xe
 *            phạm vi giá trị từ 0% đến 100%
 *
 * - speedB : tốc độ động cơ kênh B, bên PHẢI của xe
 *            phạm vi giá trị từ 0% đến 100%
 */
void Makerlabvn_SimpleMotor::car_bw(int speedA, int speedB)
{
  // Xử lý giá trị tốc độ nhận được
  speedA = calculate_speed(speedA);
  speedB = calculate_speed(speedB);

  motorA_bw(speedA); // Điều khiển motor kênh A quay ngược
  motorB_bw(speedB); // Điều khiển motor kênh B quay ngược
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển xe xoay trái
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void Makerlabvn_SimpleMotor::car_rotateL(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  motorA_bw(speed); // Điều khiển motor kênh A quay ngược
  motorB_fw(speed); // Điều khiển motor kênh B quay thuận
}

/**
 * Điều khiển xe xoay phải
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void Makerlabvn_SimpleMotor::car_rotateR(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  motorA_fw(speed); // Điều khiển motor kênh A quay thuận
  motorB_bw(speed); // Điều khiển motor kênh B quay ngược
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển xe dừng lại
 */
void Makerlabvn_SimpleMotor::car_stop()
{
  motorA_stop(); // Điều khiển motor kênh A dừng lại
  motorB_stop(); // Điều khiển motor kênh B dừng lại
}

/* ------------------------------------------------------------------------- */
/*                               HÀM ĐẶT TỐC ĐỘ                              */
/* ------------------------------------------------------------------------- */

/**
 * Đảm bảo giá trị tốc độ (%) nhận được trong khoảng 0% đến 100%
 * Đồng thời chuyển đổi tốc độ (%) sang thang (PWM) tương ứng
 */
int Makerlabvn_SimpleMotor::calculate_speed(int speed)
{
  // Đảm bảo giá trị tốc độ (%) nằm trong khoảng cho phép
  speed = constrain(speed, 0, 100);

  // Chuyển đổi giá trị tốc độ (%) sang (PWM)
  speed = map(speed, 0, 100, 0, 255);

  return speed;
}

/* ------------------------------------------------------------------------- */

Makerlabvn_SimpleMotorSixPins::Makerlabvn_SimpleMotorSixPins() {}

void Makerlabvn_SimpleMotorSixPins::setup(int pinIN1,
                                          int pinIN2,
                                          int pinIN3,
                                          int pinIN4,
                                          int pinENA,
                                          int pinENB)
{
  _pinIn1 = pinIN1;
  _pinIn2 = pinIN2;
  _pinIn3 = pinIN3;
  _pinIn4 = pinIN4;
  _pinENA = pinENA;
  _pinENB = pinENB;

  pinMode(_pinIn1, OUTPUT);
  pinMode(_pinIn2, OUTPUT);
  pinMode(_pinIn3, OUTPUT);
  pinMode(_pinIn4, OUTPUT);
  pinMode(_pinENA, OUTPUT);
  pinMode(_pinENB, OUTPUT);
}

void Makerlabvn_SimpleMotorSixPins::motorA_fw(int speed)
{
  int _speed = calculate_speed(speed);
  digitalWrite(_pinIn1, HIGH);
  digitalWrite(_pinIn2, LOW);
  analogWrite(_pinENA, _speed);
}
void Makerlabvn_SimpleMotorSixPins::motorA_bw(int speed)
{
  int _speed = calculate_speed(speed);
  digitalWrite(_pinIn1, LOW);
  digitalWrite(_pinIn2, HIGH);
  analogWrite(_pinENA, _speed);
}
void Makerlabvn_SimpleMotorSixPins::motorB_fw(int speed)
{
  int _speed = calculate_speed(speed);
  digitalWrite(_pinIn3, HIGH);
  digitalWrite(_pinIn4, LOW);
  analogWrite(_pinENB, _speed);
}
void Makerlabvn_SimpleMotorSixPins::motorB_bw(int speed)
{
  int _speed = calculate_speed(speed);
  digitalWrite(_pinIn3, LOW);
  digitalWrite(_pinIn4, HIGH);
  analogWrite(_pinENB, _speed);
}

void Makerlabvn_SimpleMotorSixPins::motorA_stop()
{
  digitalWrite(_pinIn1, LOW);
  digitalWrite(_pinIn2, LOW);
  analogWrite(_pinENA, 0);
} // Điều khiển motor kênh A dừng lại
void Makerlabvn_SimpleMotorSixPins::motorB_stop()
{
  digitalWrite(_pinIn3, LOW);
  digitalWrite(_pinIn4, LOW);
  analogWrite(_pinENB, 0);
} // Điều khiển motor kênh B dừng lại

void Makerlabvn_SimpleMotorSixPins::car_fw(int speedA, int speedB)
{
  motorA_fw(speedA);
  motorB_fw(speedB);
} // Điều khiển xe đi tới
void Makerlabvn_SimpleMotorSixPins::car_bw(int speedA, int speedB)
{
  motorA_bw(speedA);
  motorB_bw(speedB);
} // Điều khiển xe đi lùi
void Makerlabvn_SimpleMotorSixPins::car_rotateL(int speed)
{
  motorA_bw(speed);
  motorB_fw(speed);
} // Điều khiển xe xoay trái
void Makerlabvn_SimpleMotorSixPins::car_rotateR(int speed)
{
  motorA_fw(speed);
  motorB_bw(speed);
} // Điều khiển xe xoay phải

void Makerlabvn_SimpleMotorSixPins::car_stop()
{
  motorA_stop();
  motorB_stop();
}

int Makerlabvn_SimpleMotorSixPins::calculate_speed(int speed)
{
  speed = constrain(speed, 0, 100);

  // Chuyển đổi giá trị tốc độ (%) sang (PWM)
  speed = map(speed, 0, 100, 0, 255);

  return speed;
}

void Motor_lib::begin(int pwm_, int in1_, int in2_){
  this->in1 = in1_;
  this->in2 = in2_;
  this->pwm = pwm_;

  pinMode(this->in1, OUTPUT);
  pinMode(this->in2, OUTPUT);
  pinMode(this->pwm, OUTPUT);

}

void Motor_lib::forward(int iSpeed){
  digitalWrite(this->in1, 1);
  digitalWrite(this->in2, 0);
  analogWrite(this->pwm, iSpeed);
  this->resetTimeRun();
}

void Motor_lib::backward(int iSpeed){
  digitalWrite(this->in1, 0);
  digitalWrite(this->in2, 1);
  analogWrite(this->pwm, iSpeed);
  this->resetTimeRun();
}

void Motor_lib::stop(){
  digitalWrite(this->in1, 0);
  digitalWrite(this->in2, 0);
  analogWrite(this->pwm, 0);
}

void Motor_lib::setTimeRun(unsigned long ul_timerun_){
  this->timeRun = ul_timerun_;
}

void Motor_lib::checkStop(){
  if(this->timeRun == 0) return;
  if(millis() - this->lastTime >= this->timeRun){
      this->stop();
  }
}

void Motor_lib::resetTimeRun(){
  this->lastTime = millis();
}