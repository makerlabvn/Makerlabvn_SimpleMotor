/**
 * Kiểm tra điều khiển xe kết hợp 2 kênh A và B
 * https://hshop.vn/mach-makeredu-creator-arduino-uno-compatible
 */

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Makerlabvn_SimpleMotor.h"

/* ------------------------------------------------------------------------- */
/*                                   DEFINE                                  */
/* ------------------------------------------------------------------------- */

// Creator
#define PIN_ENA 5    //! (~)
#define PIN_IN1 7
#define PIN_IN2 4
#define PIN_IN3 9
#define PIN_IN4 8
#define PIN_ENB 6    //! (~)

/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */

Makerlabvn_SimpleMotor demo;

/* ------------------------------------------------------------------------- */
/*                                RUN ONE TIME                               */
/* ------------------------------------------------------------------------- */

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");

  demo.setup(PIN_ENA, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4, PIN_ENB);

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

  Serial.println("Xoay trái tốc độ 10%.");
  demo.car_rotateL(30);
  delay(5000);

  Serial.println("Xoay phải tốc độ 50%.");
  demo.car_rotateR(20);
  delay(5000);

  /* ----------------------------------------------------------------------- */

  Serial.println("Dừng lại.");
  demo.car_stop();
  delay(5000);
}