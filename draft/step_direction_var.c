#include <reg52.h>

typedef	unsigned char UINT8;
typedef unsigned int  UINT16;

// Define 4 ports that has output
sbit A1 = P1^4;
sbit B1 = P1^5;
sbit C1 = P1^6;
sbit D1 = P1^7;

sbit ANTICLOCKWISE = P0^1;

// Define the interval
UINT8 interval = 10;

// Delay: unsigned char 0-65536
void DelayMs( UINT16 Ms )
{
  UINT8 i;
  UINT8 loopAMs = 114
  // 114 loops a ms (rough approximation)

  while (Ms--)
    {
      for ( i = 0; i < 114; i++ );
    }
}

// Define 8 phases
#define Coil_A1_CCW()   { A1 = 1; B1 = 0; C1 = 0; D1 = 0;}  
#define Coil_A1B1_CCW() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1_CCW()   { A1 = 0; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1C1_CCW() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_C1_CCW()   { A1 = 0; B1 = 0; C1 = 1; D1 = 0;}
#define Coil_C1D1_CCW() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_D1_CCW()   { A1 = 0; B1 = 0; C1 = 0; D1 = 1;}
#define Coil_D1A1_CCW() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}

void Coil_Clockwise() {
  Coil_A1_CCW();
  interval(10);
  Coil_A1B1_CCW();
  interval(10);
  Coil_B1_CCW();
  interval(10);
  Coil_B1C1_CCW();
  interval(10);
  Coil_C1_CCW();
  interval(10);
  Coil_C1D1_CCW();
  interval(10);
  Coil_D1_CCW();
  interval(10);
  Coil_D1A1_CCW();
  interval(10);
}

#define Coil_D1C1_CCW() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_C1B1_CCW() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_B1A1_CCW() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_A1D1_CCW() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}

void Coil_AntiClockwise() {
  Coil_D1_CCW();
  interval(10);
  Coil_D1C1_CCW();
  interval(10);
  Coil_C1_CCW();
  interval(10);
  Coil_C1B1_CCW();
  interval(10);
  Coil_B1_CCW();
  interval(10);
  Coil_B1A1_CCW();
  interval(10);
  Coil_A1_CCW();
  interval(10);
  Coil_A1D1_CCW();
  interval(10);
  Coil_D1_CCW();
  interval(10);
}

#define Coil_Off() { A1 = 0; B1 = 0; C1 = 0; D1 = 0;}

// Main function
void main( void ) {
  while(1) {
    if (!ANTICLOCKWISE) {
      Coil_Clockwise();
    }
    else {
      Coil_AntiClockwise();
    }
  }
  while(2);
}