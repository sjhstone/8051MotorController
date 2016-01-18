#include <reg52.h>

/* Variable Speed and Orientation Step Motor Driver
 * Chen Chen (Roy Chan), Shi Jiahe (STONE), JAN 2016
 * SIST, ShanghaiTech University
 * ---------------------------------------------------
 */

typedef unsigned char UINT8;
typedef unsigned int  UINT16;

// 4 output ports
sbit A1 = P1^4;
sbit B1 = P1^5;
sbit C1 = P1^6;
sbit D1 = P1^7;

// 3 input ports
sbit SLOWER = P0^0;
sbit FASTER = P0^1;
sbit chgDir = P0^2;

// Marco that defines 8 cis-rotation phases
#define Coil_A1_CCW()   { A1 = 1; B1 = 0; C1 = 0; D1 = 0;}  
#define Coil_A1B1_CCW() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1_CCW()   { A1 = 0; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1C1_CCW() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_C1_CCW()   { A1 = 0; B1 = 0; C1 = 1; D1 = 0;}
#define Coil_C1D1_CCW() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_D1_CCW()   { A1 = 0; B1 = 0; C1 = 0; D1 = 1;}
#define Coil_D1A1_CCW() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}
// Marco that defines 4 trans-rotation phases
#define Coil_D1C1_CCW() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_C1B1_CCW() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_B1A1_CCW() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_A1D1_CCW() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}
// Marco that defines an off phase to save power
#define Coil_Off() { A1 = 0; B1 = 0; C1 = 0; D1 = 0;}


void delay(UINT16 units) {
  UINT8 loopPerUnit = 114;
  // will delay about 1 ms if loopPerUnit = 114 
  while (units--) {
    for (i = 0; i < loopPerUnit; i++);
  }
}

void main(void) {
  UINT8 interval;
  interval = 100;
  while(1) {
    if (!SLOWER) {
      interval += interval < 151 ? 1 : 0;
    }
    if (!FASTER) {
      interval -= interval > 49 ? 1 : 0;
    }
    if (!chgDir) {
      Coil_A1_CCW();   delay(interval);
      Coil_A1B1_CCW(); delay(interval);
      Coil_B1_CCW();   delay(interval);
      Coil_B1C1_CCW(); delay(interval);
      Coil_C1_CCW();   delay(interval);
      Coil_C1D1_CCW(); delay(interval);
      Coil_D1_CCW();   delay(interval);
      Coil_D1A1_CCW(); delay(interval);
    } else {
      Coil_D1_CCW();   delay(interval);
      Coil_D1C1_CCW(); delay(interval);
      Coil_C1_CCW();   delay(interval);
      Coil_C1B1_CCW(); delay(interval);
      Coil_B1_CCW();   delay(interval);
      Coil_B1A1_CCW(); delay(interval);
      Coil_A1_CCW();   delay(interval);
      Coil_A1D1_CCW(); delay(interval);
      Coil_D1_CCW();   delay(interval);
    }
  }
}