#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#define LED_0 0x0E
#define LED_1 0X0D
#define LED_2 0x0B
#define LED_3 0x07
unsigned char SECUENCIA[]={LED_0, LED_1, LED_2, LED_3};
void delay_ms(unsigned int tiempo_ms)
{

   unsigned int ciclos_de_tiempo;
   ciclos_de_tiempo=tiempo_ms/8;
   do{
		SRTISC=0b00000001;
		do{
			__RESET_WATCHDOG();
		}while(SRTISC_RTIF==0);
		SRTISC_RTIACK=1;
	}while(--ciclos_de_tiempo);
	SRTISC=0b00000000;
	
}
void delay_512_ms(void)
{
  SRTISC=0b00000110;//configurar rti
  do
  {
	  __RESET_WATCHDOG();
  }while(SRTISC_RTIF==0);//mientras bandera apagada
  SRTISC_RTIACK=1;//limpiar bandera
  SRTISC=0b00000000;//detener
}
void main(void) {
  unsigned char i =0;
  EnableInterrupts;
  PTBDD=0x0F;
  PTAPE_PTAPE2=1;
  /* include your code here */
  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */
    PTBD=SECUENCIA[i];
	delay_ms(500);
    if(PTAD_PTAD2==0)
    {
    	i++;
    	if(i==4)
    	{
    		i=0;
    	}
    }
    else
    {
    	i--;
    	if(i==255){
    		i=3;
    	}
    }
  } /* loop forever */
  /* please make sure that you never leave main */
}
