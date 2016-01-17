#include<reg52.h>     //Header file

sbit LED = P1^1;      //Define Led
sbit Flag = P0^0;
unsigned char CYCLE;  //Define period
unsigned char PWM_ON ;//Define the time of high level

void delay(unsigned int cnt) {
    while(--cnt);
}


main() {

  while(1) {
    if(Flag) {
      LED=0;
      PWM_ON++;
    }
    else {
      LED=1;
      PWM_ON--;
    }

  }

}
// /******************************************************************/
// /*                    Timer interrupt routine                     */
// /******************************************************************/
// void tim(void) interrupt 1 using 1
// {
// static unsigned char count; 
// TH0=(65536-100)/256; 
// TL0=(65536-100)%256;     //0.1mS 

// if (count==PWM_ON)
//     {
//      LED = 1;             
//     }
//   count++;
// if(count == CYCLE)
//     {
//     count=0;
//     if(PWM_ON!=0)       
//        LED = 0;        

//     }

// }