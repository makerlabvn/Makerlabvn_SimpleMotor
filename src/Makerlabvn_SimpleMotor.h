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
#include "kxnTask.h"
#include "Makerlabvn_I2C_Motor_Driver.h"

enum{
  Makerlabvn_SimpleMotor_Type_L298_6Pin,
  Makerlabvn_SimpleMotor_Type_L298_4Pin,
  Makerlabvn_SimpleMotor_Type_I2C,
};

enum{
  Makerlabvn_SimpleMotor_State_moveFrom0,
  Makerlabvn_SimpleMotor_State_moveFromCW,
  Makerlabvn_SimpleMotor_State_moveFromCCW,
  Makerlabvn_SimpleMotor_State_StopThenMoveFrom0,
};

/* ------------------------------------------------------------------------- */
/*                                   CLASS                                   */
/* ------------------------------------------------------------------------- */

class Makerlabvn_SimpleMotor: public kxnTask
{
private:
  uint8_t type;
  uint8_t i2cAddress;
  int kxnSpeedA, kxnSpeedB;
  int lastSpeedA, lastSpeedB;
  Makerlabvn_I2C_Motor_Driver *i2cMotorDriver;
public:
  /* ------------------------------- HÀM TẠO ------------------------------- */
  Makerlabvn_SimpleMotor(){}
  
  Makerlabvn_SimpleMotor(
      uint8_t pinIn1, uint8_t pinIn2,
      uint8_t pinIn3, uint8_t pinIn4
  );

  Makerlabvn_SimpleMotor(
      uint8_t pinEnA, uint8_t pinIn1, uint8_t pinIn2,
      uint8_t pinIn3, uint8_t pinIn4, uint8_t pinEnB
  );

  Makerlabvn_SimpleMotor(
    uint8_t paI2cAddress
  );

  void setup(uint8_t paAddress);

  void setup(
    uint8_t pinIn1, uint8_t pinIn2,
    uint8_t pinIn3, uint8_t pinIn4
  );
  
  void setup(
    uint8_t pinEnA, uint8_t pinIn1, uint8_t pinIn2,
    uint8_t pinIn3, uint8_t pinIn4, uint8_t pinEnB
  );

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

  void car_run(int speedA, int speedB);

  void loop();

private:
  /* ----------------------- (BIẾN) CẤU HÌNH CÁC PIN ----------------------- */
  uint8_t _pinIn1;
  uint8_t _pinIn2;
  uint8_t _pinIn3;
  uint8_t _pinIn4;
  uint8_t _pinEnA;
  uint8_t _pinEnB;

  /* --------------------------- (HÀM) ĐẶT TỐC ĐỘ -------------------------- */

  /**
   * Đảm bảo giá trị tốc độ (%) nhận được trong khoảng 0% đến 100%
   * Đồng thời chuyển đổi tốc độ (%) sang thang (PWM) tương ứng
   */
  int calculate_speed(int speed);
};

/* ------------------------------------------------------------------------- */

#endif