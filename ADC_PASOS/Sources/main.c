#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
unsigned char ADC_value;

unsigned char range, speed;
#define MAX_SPEED  52  // 52 miliseconds per half step to achieve minimum speed of 0.2 rpm
#define MIN_SPEED  1   // 1 milisecond as maximum speed
#define SCALE 5 	   // for each 5 values in the ADC value read with 8 bit resolution, we would have one change in our speed

/* We will implement the absolut value function by using 2's complement */
unsigned char absoluteValue(unsigned char  n)
{
	n = ~n; //negation
	return n += 1;
}

interrupt VectorNumber_Vadc void ADC_ISR(void){
	range = MAX_SPEED - MIN_SPEED;
	speed = absoluteValue(ADCRL/SCALE - range);
	ADC_value=ADCRL; //for debug purposes

}

void main(void) {
  EnableInterrupts;
  /* include your code here */
  APCTL1_ADPC0=1;//pin adpc0 pa0 entrada analogica 
  //APCTL1_ADPC=0x49;
  ADCSC1=0x60;//una conversion
  
//base de tiempo 1 ms 


  for(;;) {
   
    
    do {
    	__RESET_WATCHDOG();	/* feeds the dog */
    }while(1);
  } /* loop forever */
  /* please make sure that you never leave main */
}
