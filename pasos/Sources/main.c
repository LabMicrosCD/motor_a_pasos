#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
//unsigned char arreglo_medio_paso[]={0x07,0x03,0x0B,0x09,0x0D,0x0C,0x0E,0x06}; //active low
//unsigned char arreglo_medio_paso[]={0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09}; //active high
//unsigned char arreglo_medio_paso[]={0x0E,0x0C,0x0D,0x09,0x0B,0x03,0x07,0x06}; //chacho
unsigned char arreglo_medio_paso[]={0b00001000, 0b00001100, 0b00000100, 0b00000110, 0b00000010 ,0b00000011, 0b00000001, 0b00001001}; //chacho negadp
unsigned char conteo = 0; //hasta 38s
unsigned char i=0;
interrupt 12 void MTIM(void){ //para la interrupcion 12, pag 66 manual PARA LOS LEDS
	(void) MTIMSC; //se que no lo voy a leer, (TENGO QUE LEERLO CUANDO ESTE EN 1 POR PROTOCOLO DE BORRADO)
	MTIMSC_TOF=0;// DESPUES DE LEERLO, PONERLO A 0
	//amarillo, azul , cafe verde
	if(conteo == 3){
		conteo = 0;
		//unsigned char arreglo_medio_paso[]={0x0E,0x0C,0x0D,0x09,0x0B,0x03,0x07,0x06}; //chacho
	    PTBD=arreglo_medio_paso[i];
	    i++;
	    if(i==8)
	    {
	    	i=0;
	    }
		//    PTBD=arreglo_medio_paso[i];
	}else{
		conteo++;
	}
	
}


void main(void) {
  EnableInterrupts;
  /* include your code here */
  PTBDD=0x0F;
  MTIMSC_TOIE=1;
  MTIMCLK=0x04;
  MTIMSC_TSTP=0;
  MTIMMOD=250;
  PTAPE_PTAPE2=1;
  
  
  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */

  } /* loop forever */
  /* please make sure that you never leave main */
}
