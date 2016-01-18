#include <reg52.h>

/* Variable Speed DC Motor Driver (PWM Implementation)
 * Shi Jiahe (STONE), Chen Chen (Roy Chan), JAN 2016
 * SIST, ShanghaiTech University
 * ---------------------------------------------------
 * A cycle lasts about 0.13 s by default.
 * Adding an LED at the output helps visualizing the way PWM works.
 */

typedef unsigned char UINT8;
typedef unsigned int  UINT16;

sbit PWMSignal = P1^1;  // OUT: PWM signal
sbit SpdUp     = P0^0;  // IN:  speed up
sbit SpdDn     = P0^1;  // IN:  speed down
UINT8 i;
UINT8 DutyOn = 0;

void delay(UINT16 units) {
  UINT8 loopPerUnit = 60;
  while (units--) {
    for (i = 0; i < loopPerUnit; i++);
  }
}

void main(void) {
  PWMSignal = 0;
  while(1) {
    if (!SpdUp) {
      DutyOn += DutyOn < 255 ? 1 : 0;
    }
    if (!SpdDn) {
      DutyOn -= DutyOn > 1 ? 1 : 0;
    }
    PWMSignal = 1;
    delay(DutyOn);
    PWMSignal = 0;
    delay(255 - DutyOn);
  }
}