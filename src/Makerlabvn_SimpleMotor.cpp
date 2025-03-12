/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Makerlabvn_SimpleMotor.h"

/* ------------------------------------------------------------------------- */
/*                                  HÀM TẠO                                  */
/* ------------------------------------------------------------------------- */

Makerlabvn_SimpleMotor::Makerlabvn_SimpleMotor(
  uint8_t paI2cAddress
)
{
  this->type = Makerlabvn_SimpleMotor_Type_I2C;

}

Makerlabvn_SimpleMotor::Makerlabvn_SimpleMotor(
    uint8_t pinIn1, uint8_t pinIn2,
    uint8_t pinIn3, uint8_t pinIn4)
{
  setup(pinIn1, pinIn2, pinIn3, pinIn4);
}

Makerlabvn_SimpleMotor::Makerlabvn_SimpleMotor(
      uint8_t pinEnA, uint8_t pinIn1, uint8_t pinIn2,
      uint8_t pinIn3, uint8_t pinIn4, uint8_t pinEnB)
{
  setup(pinEnA, pinIn1, pinIn2, pinIn3, pinIn4, pinEnB);
}

void Makerlabvn_SimpleMotor::setup(uint8_t paI2cAddress)
{
  this->type = Makerlabvn_SimpleMotor_Type_I2C;
  if(i2cMotorDriver != NULL){
    delete i2cMotorDriver;
  }
  i2cMotorDriver = new Makerlabvn_I2C_Motor_Driver(paI2cAddress);
  i2cMotorDriver->begin();
}

void Makerlabvn_SimpleMotor::setup(
  uint8_t pinIn1, uint8_t pinIn2,
  uint8_t pinIn3, uint8_t pinIn4
)
{
  this->type = Makerlabvn_SimpleMotor_Type_L298_4Pin;
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
  
void Makerlabvn_SimpleMotor::setup(
  uint8_t pinEnA, uint8_t pinIn1, uint8_t pinIn2,
  uint8_t pinIn3, uint8_t pinIn4, uint8_t pinEnB
)
{
  this->type = Makerlabvn_SimpleMotor_Type_L298_6Pin;
  _pinIn1 = pinIn1;
  _pinIn2 = pinIn2; // ~PWM
  _pinIn3 = pinIn3; // ~PWM
  _pinIn4 = pinIn4;
  this->_pinEnA = pinEnA;
  this->_pinEnB = pinEnB;

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
  this->lastSpeedA = speed;
  
  // Điều khiển Motor bên TRÁI quay tới
  switch (this->type)
  {
  case Makerlabvn_SimpleMotor_Type_L298_4Pin:
    /* code */
    digitalWrite(_pinIn1, LOW);
    analogWrite(_pinIn2, speed); // ~PWM
    break;
  case Makerlabvn_SimpleMotor_Type_L298_6Pin:
    /* code */
    digitalWrite(this->_pinIn1, 1);
    digitalWrite(this->_pinIn2, 0);
    analogWrite(this->_pinEnA, speed);
    break;
  
  case Makerlabvn_SimpleMotor_Type_I2C:
    i2cMotorDriver->MA(1, speed);
    break;

  default:
    break;
  }
  
  
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
  this->lastSpeedB = speed;

  // Điều khiển Motor bên PHẢI quay tới
  switch (this->type)
  {
  case Makerlabvn_SimpleMotor_Type_L298_4Pin:
    digitalWrite(_pinIn4, LOW);
    analogWrite(_pinIn3, speed); // ~PWM
    break;
  case Makerlabvn_SimpleMotor_Type_L298_6Pin:
    /* code */
    digitalWrite(this->_pinIn3, 1);
    digitalWrite(this->_pinIn4, 0);
    analogWrite(this->_pinEnB, speed);
    break;
  
  case Makerlabvn_SimpleMotor_Type_I2C:
    i2cMotorDriver->MB(1, speed);
    break;

  default:
    break;
  }
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
  this->lastSpeedA = -speed;
  // Điều khiển Motor bên TRÁI quay lùi
  switch (this->type)
  {
  case Makerlabvn_SimpleMotor_Type_L298_4Pin:
    digitalWrite(_pinIn1, HIGH);
    analogWrite(_pinIn2, 255 - speed); // ~PWM
    break;
  case Makerlabvn_SimpleMotor_Type_L298_6Pin:
    /* code */
    digitalWrite(this->_pinIn1, 0);
    digitalWrite(this->_pinIn2, 1);
    analogWrite(this->_pinEnA, speed);
    break;
  
  case Makerlabvn_SimpleMotor_Type_I2C:
    i2cMotorDriver->MA(0, speed);
    break;

  default:
    break;
  }
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
  this->lastSpeedB = -speed;
  // Điều khiển Motor bên PHẢI quay lùi
  switch (this->type)
  {
  case Makerlabvn_SimpleMotor_Type_L298_4Pin:
    digitalWrite(_pinIn4, HIGH);
    analogWrite(_pinIn3, 255 - speed); // ~PWM
    break;
  case Makerlabvn_SimpleMotor_Type_L298_6Pin:
    /* code */
    digitalWrite(this->_pinIn3, 0);
    digitalWrite(this->_pinIn4, 1);
    analogWrite(this->_pinEnB, speed);
    break;
  
  case Makerlabvn_SimpleMotor_Type_I2C:
    i2cMotorDriver->MB(0, speed);
    break;

  default:
    break;
  }
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển motor kênh A dừng lại
 */
void Makerlabvn_SimpleMotor::motorA_stop()
{
  // Điều khiển Motor bên TRÁI dừng lại
  motorA_bw(0);
}

/**
 * Điều khiển motor kênh B dừng lại
 */
void Makerlabvn_SimpleMotor::motorB_stop()
{
  // Điều khiển Motor bên PHẢI dừng lại
  motorB_bw(0);
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

void Makerlabvn_SimpleMotor::car_run(int speedA, int speedB){
  if(speedA>0){
    motorA_fw(speedA);
  }else{
    motorA_bw(-speedA);
  }

  if(speedB>0){
    motorB_fw(speedB);
  }else{
    motorB_bw(-speedB);
  }
  // speedA>0?motorA_fw(speedA):motorA_bw(speedA);
  // speedB>0?motorB_fw(speedB):motorB_bw(speedB);
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

void Makerlabvn_SimpleMotor::loop(){
  switch (getState())
  {
  case Makerlabvn_SimpleMotor_State_moveFrom0:
    
    break;
  
  default:
    break;
  }
}
/* ------------------------------------------------------------------------- */