#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
unsigned char arreglo[]={0x0E,0x0D,0x0B,0x07};
unsigned char i;

interrupt 23 void RTI_ISR(void)
{	
	SRTISC_RTIACK=1;
	PTBD=arreglo[i];
	if(PTAD_PTAD2==0)
	{
	  	i++;
	  	if(i==4)
	  	{
	  		i=0;
	  	}
	  	else
	  	{
	  		i--;
	  		if(i==255)
	  		{
	  			i=3;
	  		}
	  	}
	}
	
}



void main(void) {
  EnableInterrupts;
  /* include your code here */
  PTBDD=0xF;
  PTAPE_PTAPE2=1;
  SRTISC=0b00010110;
  i=0;
  

  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
