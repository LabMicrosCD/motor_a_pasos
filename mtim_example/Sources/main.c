#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned char arreglo_secuencia[]={0x0E,0x0D,0x0B,0x07};
unsigned char i;

interrupt 12 void RTI_ISR(void){ //para la interrupcion 12, pag 66 manual PARA LOS LEDS
	(void) MTIMSC; //se que no lo voy a leer, (TENGO QUE LEERLO CUANDO ESTE EN 1 POR PROTOCOLO DE BORRADO)
	MTIMSC_TOF=0;// DESPUES DE LEERLO, PONERLO A 0
	//TODAS LAS BANDERAS DE TODOS LOS MICROS SE APAGAN DIFERENTE
	//PTBD_PTBD7 ^=1; ESTA O LA DE ABAJO
	PTBD_PTBD7 =! PTBD_PTBD7; //CAMBIAR VALOR DEL PIN

}


void main(void) {

EnableInterrupts;
MTIMSC_TOIE=1;

PTBDD_PTBDD7=1; //LEDS DE TARJETA 6 , 7
MTIMCLK=0b00001000;
MTIMSC_TSTP=0;
MTIMMOD=250;


  for(;;) {
  
    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
/* please make sure that you never leave main */
}
