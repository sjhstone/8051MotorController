#include <reg52.h>

// Step with varing speed

typedef	unsigned char UINT8;
typedef unsigned int  UINT16;

// Define 4 ports that has output
sbit A1 = P1^4;
sbit B1 = P1^5;
sbit C1 = P1^6;
sbit D1 = P1^7;

sbit SLOWER = P0^0;
sbit FASTER = P0^1;


// Define 8 phases
#define Coil_A1_CCW()   { A1 = 1; B1 = 0; C1 = 0; D1 = 0;}  
#define Coil_A1B1_CCW() { A1 = 1; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1_CCW()   { A1 = 0; B1 = 1; C1 = 0; D1 = 0;}
#define Coil_B1C1_CCW() { A1 = 0; B1 = 1; C1 = 1; D1 = 0;}
#define Coil_C1_CCW()   { A1 = 0; B1 = 0; C1 = 1; D1 = 0;}
#define Coil_C1D1_CCW() { A1 = 0; B1 = 0; C1 = 1; D1 = 1;}
#define Coil_D1_CCW()   { A1 = 0; B1 = 0; C1 = 0; D1 = 1;}
#define Coil_D1A1_CCW() { A1 = 1; B1 = 0; C1 = 0; D1 = 1;}

#define Coil_Off()      { A1 = 0; B1 = 0; C1 = 0; D1 = 0;}

// Delay: unsigned char 0-65536
void DelayMs( UINT16 Ms )
{
	UINT8 i;
  UINT8 loopAMs = 114;
  // 114 loops a ms (rough approximation)

	while (Ms--)
  	{
    	for ( i = 0; i < 114; i++ );
  	}
}

// Main function
void main( void )
{
    UINT16 i;
    UINT8 interval;
	interval = 10;
    
    for( i = 0 ; i< 512; i++ )   // A complete cycle requires 360/(0.087890625*8) = 512 loops
    {
      if (!SLOWER) {
        interval += interval < 255 ? 1 : 0;
      }
      if (!FASTER) {
        interval -= interval > 0 ? 1 : 0;
      }
        Coil_A1_CCW()            // (5.625/64) = 0.087890625 deg for a phase
        DelayMs(interval);
        Coil_A1B1_CCW()
        DelayMs(interval);                                 
        Coil_B1_CCW()
        DelayMs(interval);
        Coil_B1C1_CCW()
        DelayMs(interval);
        Coil_C1_CCW()
        DelayMs(interval);
        Coil_C1D1_CCW()
        DelayMs(interval);
        Coil_D1_CCW()
        DelayMs(interval);
        Coil_D1A1_CCW()
        DelayMs(interval);
    }

    Coil_Off(); // Stops operation, cut the power

    while(1);   // Won't work until a RESET is triggered
}