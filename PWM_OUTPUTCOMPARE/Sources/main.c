#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
unsigned char duty_cycle;
unsigned int cuenta;
interrupt VectorNumber_Vtpmch0  void CH0_ISR(void)
{
	(void)TPMC0SC;
	TPMC0SC_CH0F=0;
	if(TPMC0SC_ELS0A==1)
		{
		TPMC0SC=0b01011000;
		TPMC0V+=10*(unsigned int)duty_cycle;	
		}
		else
		{
		TPMC0SC=0b01011100;
		TPMC0V+=10*(unsigned int)duty_cycle;	
		}
}

void main(void) {
  EnableInterrupts;
  /* include your code here */
  duty_cycle=50;
  cuenta=0;
  PTADD_PTADD0=1;//salida y el pin se carga con 0
  TPMSC=0b00001010;
  TPMC0SC=0b01011100;
  TPMC0V=(100-(unsigned int)duty_cycle)*10;
  

  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
