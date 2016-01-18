#include <reg52.h>

/* EE111 Project: Motor Controller
 * Shi Jiahe (STONE), Chen Chen (Roy Chan), JAN 2016
 * SIST, ShanghaiTech University
 * ---------------------------------------------------
 */

typedef unsigned char UINT8;
typedef unsigned int  UINT16;

UINT8 i;

// Generalized input ports
sbit M_TYPE = P0^3;  // IN: motor type
sbit SpdUp  = P0^0;  // IN: speed up
sbit SpdDn  = P0^1;  // IN: speed down

/*
 * DC I/O
 */
sbit DCM_OUT = P1^1;
UINT8 DC_DutyOn = 65;
/*
 * Step I/O
 */
sbit STP_dir = P0^2;
sbit A1 = P1^4;
sbit B1 = P1^5;
sbit C1 = P1^6;
sbit D1 = P1^7;

// Marco that defines 8 cis-rotation phases
#define Coil_A1_ph()   { A1 = 1; B1 = 0; C1 = 0; D1 = 0;}  
#define Coil_A1B1_ph() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1_ph()   { A1 = 0; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1C1_ph() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_C1_ph()   { A1 = 0; B1 = 0; C1 = 1; D1 = 0;}
#define Coil_C1D1_ph() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_D1_ph()   { A1 = 0; B1 = 0; C1 = 0; D1 = 1;}
#define Coil_D1A1_ph() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}
// Marco that defines 4 trans-rotation phases
#define Coil_D1C1_ph() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_C1B1_ph() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_B1A1_ph() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_A1D1_ph() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}
// Marco that defines an off phase to save power
#define Coil_Off() { A1 = 0; B1 = 0; C1 = 0; D1 = 0;}

void DC_delay(UINT16 units) {
  UINT8 loopPerUnit = 60;
  while (units--) {
    for (i = 0; i < loopPerUnit; i++);
  }
}

void STP_delay(UINT16 units) {
  UINT8 loopPerUnit = 15;
  // will delay about 1 ms if loopPerUnit = 114 
  while (units--) {
    for (i = 0; i < loopPerUnit; i++);
  }
}

void init(void) {
  Coil_Off()
  DCM_OUT = 0;
}

void runDC(void) {
  bit initState = M_TYPE;
  while(1) {
    if (M_TYPE != initState) {
      return;
    }
    if (!SpdUp) {
      DC_DutyOn += DC_DutyOn < 255 ? 1 : 0;
    } else if (!SpdDn) {
      DC_DutyOn -= DC_DutyOn > 64 ? 1 : 0;
    }
    DCM_OUT = 1; DC_delay(DC_DutyOn);
    DCM_OUT = 0; DC_delay(255 - DC_DutyOn);
  }
}

void runStep(void) {
  bit initState = M_TYPE;
  UINT8 STP_itv;
  STP_itv = 50;
  while(1) {
    if (M_TYPE != initState) {
      return;
    }
    if (!SpdUp) {
      STP_itv -= STP_itv > 10 ? 1 : 0;
    } else if (!SpdDn) {
      STP_itv += STP_itv < 90 ? 1 : 0;
    }
    if (!STP_dir) {
      Coil_A1_ph();   STP_delay(STP_itv);
      Coil_A1B1_ph(); STP_delay(STP_itv);
      Coil_B1_ph();   STP_delay(STP_itv);
      Coil_B1C1_ph(); STP_delay(STP_itv);
      Coil_C1_ph();   STP_delay(STP_itv);
      Coil_C1D1_ph(); STP_delay(STP_itv);
      Coil_D1_ph();   STP_delay(STP_itv);
      Coil_D1A1_ph(); STP_delay(STP_itv);
    } else {
      Coil_D1_ph();   STP_delay(STP_itv);
      Coil_D1C1_ph(); STP_delay(STP_itv);
      Coil_C1_ph();   STP_delay(STP_itv);
      Coil_C1B1_ph(); STP_delay(STP_itv);
      Coil_B1_ph();   STP_delay(STP_itv);
      Coil_B1A1_ph(); STP_delay(STP_itv);
      Coil_A1_ph();   STP_delay(STP_itv);
      Coil_A1D1_ph(); STP_delay(STP_itv);
      Coil_D1_ph();   STP_delay(STP_itv);
    }
  }
}

void main(void) {
  while (1) {
    if (M_TYPE) {
      init();
      runStep();
    } else {
      init();
      runDC();
    }
  }
}