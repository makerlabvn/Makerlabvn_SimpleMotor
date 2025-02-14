#ifndef MKL_SIMPLE_MOTOR_H
#define MKL_SIMPLE_MOTOR_H

/**
 * Quy ước:
 * -" Kênh A" của driver điều khiển "động cơ bên TRÁI" của xe.
 * - "Kênh B" của driver điều khiển "động cơ bên PHẢI" của xe.
 */

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include <Arduino.h>

/* ------------------------------------------------------------------------- */
/*                                   CLASS                                   */
/* ------------------------------------------------------------------------- */

class Makerlabvn_SimpleMotor
{
public:
  /* ------------------------------- HÀM TẠO ------------------------------- */
  Makerlabvn_SimpleMotor();
  Makerlabvn_SimpleMotor(
      int pinIn1, int pinIn2,
      int pinIn3, int pinIn4);

  /* ------------------------- HÀM ĐIỀU KHIỂN MOTOR ------------------------ */

  void motorA_fw(int speed); // Điều khiển motor kênh A quay thuận
  void motorB_fw(int speed); // Điều khiển motor kênh B quay thuận

  void motorA_bw(int speed); // Điều khiển motor kênh A quay ngược
  void motorB_bw(int speed); // Điều khiển motor kênh B quay ngược

  void motorA_stop(); // Điều khiển motor kênh A dừng lại
  void motorB_stop(); // Điều khiển motor kênh B dừng lại

  /* -------------------------- HÀM ĐIỀU KHIỂN XE -------------------------- */

  virtual void car_fw(int speedA, int speedB); // Điều khiển xe đi tới
  virtual void car_bw(int speedA, int speedB); // Điều khiển xe đi lùi

  virtual void car_rotateL(int speed); // Điều khiển xe xoay trái
  virtual void car_rotateR(int speed); // Điều khiển xe xoay phải

  virtual void car_stop(); // Điều khiển xe dừng lại

private:
  /* ----------------------- (BIẾN) CẤU HÌNH CÁC PIN ----------------------- */
  int _pinIn1;
  int _pinIn2;
  int _pinIn3;
  int _pinIn4;

  /* --------------------------- (HÀM) ĐẶT TỐC ĐỘ -------------------------- */

  /**
   * Đảm bảo giá trị tốc độ (%) nhận được trong khoảng 0% đến 100%
   * Đồng thời chuyển đổi tốc độ (%) sang thang (PWM) tương ứng
   */
  int calculate_speed(int speed);
};

class Makerlabvn_SimpleMotorSixPins
{
public:
  /* ------------------------------- HÀM TẠO ------------------------------- */
  Makerlabvn_SimpleMotorSixPins();

  void setup(int pinIN1,
             int pinIN2,
             int pinIN3,
             int pinIN4,
             int pinENA,
             int pinENB);

  /* ------------------------- HÀM ĐIỀU KHIỂN MOTOR ------------------------ */

  void motorA_fw(int speed); // Điều khiển motor kênh A quay thuận
  void motorB_fw(int speed); // Điều khiển motor kênh B quay thuận

  void motorA_bw(int speed); // Điều khiển motor kênh A quay ngược
  void motorB_bw(int speed); // Điều khiển motor kênh B quay ngược

  void motorA_stop(); // Điều khiển motor kênh A dừng lại
  void motorB_stop(); // Điều khiển motor kênh B dừng lại

  /* -------------------------- HÀM ĐIỀU KHIỂN XE -------------------------- */

  void car_fw(int speedA, int speedB); // Điều khiển xe đi tới
  void car_bw(int speedA, int speedB); // Điều khiển xe đi lùi

  void car_rotateL(int speed); // Điều khiển xe xoay trái
  void car_rotateR(int speed); // Điều khiển xe xoay phải

  void car_stop(); // Điều khiển xe dừng lại

private:
  /* ----------------------- (BIẾN) CẤU HÌNH CÁC PIN ----------------------- */
  int _pinIn1;
  int _pinIn2;
  int _pinIn3;
  int _pinIn4;
  int _pinENA;
  int _pinENB;

  /* --------------------------- (HÀM) ĐẶT TỐC ĐỘ -------------------------- */

  /**
   * Đảm bảo giá trị tốc độ (%) nhận được trong khoảng 0% đến 100%
   * Đồng thời chuyển đổi tốc độ (%) sang thang (PWM) tương ứng
   */
  int calculate_speed(int speed);
};

/* ------------------------------------------------------------------------- */
class Motor_lib
{
public:
  uint8_t in1;
  uint8_t in2;
  uint8_t pwm;
  unsigned long lastTime, timeRun;

  // motor(int);
  void begin(int pwm_, int in1_, int in2_);
  void forward(int iSpeed);
  void backward(int iSpeed);
  void stop();
  void setTimeRun(unsigned long ul_timerun_);
  void checkStop();
  void resetTimeRun();
};

class TwoMotor_lib : public Makerlabvn_SimpleMotor
{
private:
  Motor_lib *_motorA;
  Motor_lib *_motorB;

  int calculate(int speed)
  {
    speed = constrain(speed, 0, 100);
        // Chuyển đổi giá trị tốc độ (%) sang (PWM)
        speed = map(speed, 0, 100, 0, 255);
    return speed;
  }

public:
  void begin(Motor_lib &motorA, Motor_lib &motorB)
  {
    _motorA = &motorA;
    _motorB = &motorB;
  }

  void car_fw(int speedA, int speedB) override
  {

    speedA = calculate(speedA);
    speedB = calculate(speedB);

    _motorA->forward(speedA);
    _motorB->forward(speedB);

  } // Điều khiển xe đi tới

  void car_bw(int speedA, int speedB) override
  {

    speedA = calculate(speedA);
    speedB = calculate(speedB);

    _motorA->backward(speedA);
    _motorB->backward(speedB);

  } // Điều khiển xe đi lùi

  void car_rotateL(int speed) override
  {
    speed = calculate(speed);
    _motorA->backward(speed);
    _motorB->forward(speed);
  } // Điều khiển xe xoay trái
  void car_rotateR(int speed) override
  {
    speed = calculate(speed);
    _motorA->forward(speed);
    _motorB->backward(speed);
  } // Điều khiển xe xoay phải

  void car_stop() override
  {
    _motorA->stop();
    _motorB->stop();
  } // Điều khiển xe dừng lại
};

#endif