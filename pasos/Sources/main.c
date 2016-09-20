#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
//unsigned char arreglo_medio_paso[]={0x07,0x03,0x0B,0x09,0x0D,0x0C,0x0E,0x06}; //active low
//unsigned char arreglo_medio_paso[]={0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09}; //active high
//unsigned char arreglo_medio_paso[]={0x0E,0x0C,0x0D,0x09,0x0B,0x03,0x07,0x06}; //chacho
//unsigned char arreglo_medio_paso[]={0b11110111, 0b11110011, 0b11111011, 0b11111001, 0b11111101 ,0b11111100, 0b11111110, 0b11110110};
unsigned char arreglo_medio_paso[]={0b00001000, 0b00001100, 0b00000100, 0b00000110, 0b00000010 ,0b00000011, 0b00000001, 0b00001001}; //chacho negadp
unsigned int conteo = 0; 
unsigned int i=0;
unsigned int ADC_value;
unsigned int cuentas;
unsigned int contando=0;


interrupt 12 void MTIM(void){ //para la interrupcion 12, pag 66 manual PARA LOS LEDS
	(void) MTIMSC; //se que no lo voy a leer, (TENGO QUE LEERLO CUANDO ESTE EN 1 POR PROTOCOLO DE BORRADO)
	MTIMSC_TOF=0;// DESPUES DE LEERLO, PONERLO A 0
	//amarillo, azul-negro , cafe verde
	/*
	if(conteo==cuentas){
		 PTBD=arreglo_medio_paso[i];
		 i++;
			    if(i==8)
			    {
			    	i=0;
			    }
		conteo=0;
	}else{
		conteo++;
	}*/

		if(contando==conteo){
			conteo=0;
			contando=cuentas;
			PTBD=arreglo_medio_paso[i++];
			if(i==8){
				i=0;
			}
		}else{
			conteo++;
		}



}
void ADC_Init(void){
	  APCTL1_ADPC0=1;//pin adpc0 pa0 entrada analogica 
	  ADCSC1=0x20;//una conversion

}

void ADC_Convert(){
	if(ADCSC1_COCO){
		cuentas = ((49*(unsigned int)ADCRL)/255+3);
	}
}


void main(void) {
  EnableInterrupts;
  PTBDD=0x0F;
  MTIMSC_TOIE=1;
  MTIMCLK=0x04;
  MTIMSC_TSTP=0;
  MTIMMOD=250;
  PTAPE_PTAPE2=1;
  //adc
  //adc init
  ADC_Init();
  

  for(;;) {
	  ADC_Convert();
    __RESET_WATCHDOG();	/* feeds the dog */

  } /* loop forever */
  /* please make sure that you never leave main */
}
