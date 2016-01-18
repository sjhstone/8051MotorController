#include <reg52.h>

/*
  Stepper Part
*/

typedef unsigned char UINT8;
typedef unsigned int  UINT16;

// Define 4 ports that has output
sbit A1 = P1^4;
sbit B1 = P1^5;
sbit C1 = P1^6;
sbit D1 = P1^7;

sbit ANTICLOCKWISE = P0^1;

// Define 8 phases
#define Coil_A1_CCW()   { A1 = 1; B1 = 0; C1 = 0; D1 = 0;}  
#define Coil_A1B1_CCW() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1_CCW()   { A1 = 0; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1C1_CCW() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_C1_CCW()   { A1 = 0; B1 = 0; C1 = 1; D1 = 0;}
#define Coil_C1D1_CCW() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_D1_CCW()   { A1 = 0; B1 = 0; C1 = 0; D1 = 1;}
#define Coil_D1A1_CCW() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}
#define Coil_D1C1_CCW() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_C1B1_CCW() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_B1A1_CCW() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_A1D1_CCW() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}

#define Coil_Off() { A1 = 0; B1 = 0; C1 = 0; D1 = 0;}

// Delay: unsigned char 0-65536
void delay( UINT16 Ms )
{
  UINT8 i;
  UINT8 loopAMs = 114;
  while (Ms--) {
    for ( i = 0; i < 114; i++ );
  }
}

void dc_delay(unsigned int cnt) {
  while(cnt--);
}
/*
  DC Part
*/
sbit LED = P1^1;      //Define Led
sbit Flag = P0^0;
unsigned char CYCLE;  //Define period
unsigned char PWM_ON ;//Define the time of high level

/*
  Switcher
*/
sbit Switcher = P0^2; // 0 = DC, 1 = Stepper


// Main function
void main( void ) {
  UINT8 s_interval;
  UINT8 dc_interval;
  s_interval = 100;
  dc_interval = 20000;
  while(1) {
    if (!Switcher) {
      LED = 0;
      if(Flag) {
        PWM_ON++;
      }
      else {
        PWM_ON--;
      }
      if(!PWM_ON){
        LED=1;
      }
      dc_delay(dc_interval-PWM_ON);
    }
    if (Switcher) {
      if (!ANTICLOCKWISE) {
        Coil_A1_CCW();
        delay(s_interval);
        Coil_A1B1_CCW();
        delay(s_interval);
        Coil_B1_CCW();
        delay(s_interval);
        Coil_B1C1_CCW();
        delay(s_interval);
        Coil_C1_CCW();
        delay(s_interval);
        Coil_C1D1_CCW();
        delay(s_interval);
        Coil_D1_CCW();
        delay(s_interval);
        Coil_D1A1_CCW();
        delay(s_interval);
      }
      else {
        Coil_D1_CCW();
        delay(s_interval);
        Coil_D1C1_CCW();
        delay(s_interval);
        Coil_C1_CCW();
        delay(s_interval);
        Coil_C1B1_CCW();
        delay(s_interval);
        Coil_B1_CCW();
        delay(s_interval);
        Coil_B1A1_CCW();
        delay(s_interval);
        Coil_A1_CCW();
        delay(s_interval);
        Coil_A1D1_CCW();
        delay(s_interval);
        Coil_D1_CCW();
        delay(s_interval);
      }
    }
  }
}