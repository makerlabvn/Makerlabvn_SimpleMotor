/**
 * Kiểm tra điều khiển xe kết hợp 2 kênh A và B
 */

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Makerlabvn_SimpleMotor.h"

/* ------------------------------------------------------------------------- */
/*                                   DEFINE                                  */
/* ------------------------------------------------------------------------- */

/**
 * Phần cấp nguồn cho Driver
 * +12V - ... có thể cấp nguồn trong khoảng 9V~6V
 * GND  - GND
 *
 * Dùng Jumper kết nối (mặc định)
 * ENA  - 5V
 * ENB  - 5V
 *
 * L298 : Arduino
 * IN1  : D4
 * IN2  : D5 (~)
 * IN3  : D6 (~)
 * IN4  : D7
 */
#define PIN_IN1 4 //! D4
#define PIN_IN2 5 //! D5 (~)
#define PIN_IN3 6 //! D6 (~)
#define PIN_IN4 7 //! D7

// #define PIN_ENA 5    //! (~)
// #define PIN_IN1 7
// #define PIN_IN2 4
// #define PIN_IN3 9
// #define PIN_IN4 8
// #define PIN_ENB 6    //! (~)

/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */

Makerlabvn_SimpleMotor demo(PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4);
// Makerlabvn_SimpleMotor demo(PIN_ENA, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4, PIN_ENB);
// Makerlabvn_SimpleMotor demo(0x64); // I2C Motor Driver

/* ------------------------------------------------------------------------- */
/*                                RUN ONE TIME                               */
/* ------------------------------------------------------------------------- */

void setup()
{
  Serial.begin(115200);
}

/* ------------------------------------------------------------------------- */
/*                                    MAIN                                   */
/* ------------------------------------------------------------------------- */

void loop()
{
  Serial.println("Điều khiển xe...");
  Serial.println();
  delay(1000);

  /* ----------------------------------------------------------------------- */

  Serial.println("Đi thẳng tốc độ 100%.");
  demo.car_fw(100, 100);
  delay(5000);

  Serial.println("Đi thẳng tốc độ 100%, rẽ trái.");
  demo.car_fw(0, 100);
  delay(5000);

  Serial.println("Đi thẳng tốc độ 100%, rẽ phải.");
  demo.car_fw(100, 0);
  delay(5000);

  /* ----------------------------------------------------------------------- */

  Serial.println("Đi lùi tốc độ 100%.");
  demo.car_bw(100, 100);
  delay(5000);

  Serial.println("Đi lùi tốc độ 100%, rẽ trái.");
  demo.car_bw(0, 100);
  delay(5000);

  Serial.println("Đi lùi tốc độ 100%, rẽ phải.");
  demo.car_bw(100, 0);
  delay(5000);

  /* ----------------------------------------------------------------------- */

  Serial.println("Xoay trái tốc độ 50%.");
  demo.car_rotateL(50);
  delay(5000);

  Serial.println("Xoay phải tốc độ 50%.");
  demo.car_rotateR(50);
  delay(5000);

  /* ----------------------------------------------------------------------- */

  Serial.println("Dừng lại.");
  demo.car_stop();
  delay(5000);
}