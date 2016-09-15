#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
unsigned int Tv;
unsigned int frec;
interrupt VectorNumber_Vtpmch0  void CH0_ISR(void)
{
	(void)TPMC0SC;
	TPMC0SC_CH0F=0;
	Tv=TPMC0V-Tv;
	frec=1000000/Tv;
	Tv=TPMC0V;

}


//num overflows*65530 +t2-t1     t2-t1+(over-1)65536


void main(void) {
  EnableInterrupts;
  /* include your code here */
  Tv=0;
  TPMSC=0b00001010;
  TPMC0SC=0b01000100;

  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
