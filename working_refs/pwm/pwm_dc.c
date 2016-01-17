/*-----------------------------------------------
  PWM DC Motor Control
 
------------------------------------------------*/

#include<reg52.h>     //Header file

sbit LED = P1^1;      //Define Led
unsigned char CYCLE;  //Define period
unsigned char PWM_ON ;//Define the time of high level
/******************************************************************/
/*                    Delay routine                               */
/******************************************************************/
void delay(unsigned int cnt)
{
 while(--cnt);
}
/******************************************************************/
/*                    main routine                                */
/******************************************************************/
main()
{
bit Flag;

TMOD |=0x01;              //Set timer
TH0=(65536-100)/256; 
TL0=(65536-100)%256;      //Timer=0.1mS 
IE= 0x82;                 //Enable interrupt
TR0=1;

CYCLE =10;   // 10;               // You can change the value 
while(!Flag)
  {
   delay(20000);          //Delay time 
   PWM_ON++;              //Speed up
     {                    //You can add some other functions here 
      Flag=1;
	  }
  }

 while(Flag)              //Speed down 
  {
   delay(20000);
   PWM_ON--;
   if(PWM_ON == 0)
     {
      Flag=0;
	  }
  }
}
/******************************************************************/
/*                    Timer interrupt routine                     */
/******************************************************************/
void tim(void) interrupt 1 using 1
{
static unsigned char count; 
TH0=(65536-100)/256; 
TL0=(65536-100)%256;     //0.1mS 

if (count==PWM_ON)
    {
     LED = 1;             
    }
  count++;
if(count == CYCLE)
    {
    count=0;
	if(PWM_ON!=0)       
	   LED = 0;        

    }

}