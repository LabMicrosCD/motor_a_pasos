#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
//unsigned char arreglo_medio_paso[]={0x07,0x03,0x0B,0x09,0x0D,0x0C,0x0E,0x06}; //active low
//unsigned char arreglo_medio_paso[]={0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09}; //active high
//unsigned char arreglo_medio_paso[]={0x0E,0x0C,0x0D,0x09,0x0B,0x03,0x07,0x06}; //chacho
//unsigned char arreglo_medio_paso[]={0b11110111, 0b11110011, 0b11111011, 0b11111001, 0b11111101 ,0b11111100, 0b11111110, 0b11110110};
#define MOTOR_STRING_PORT				B	/* Specify the digital port where the LED string is connected */
#define MOTOR_STRING_PIN_START		0   /* Specify the starting pin on the digital port where teh LED String is connected */

unsigned char arreglo_medio_paso[]={0b00001000, 0b00001100, 0b00000100, 0b00000110, 0b00000010 ,0b00000011, 0b00000001, 0b00001001}; //chacho negadp
unsigned char conteo = 0;
unsigned char i=0;
unsigned char ADC_value;
unsigned char speed, range;
#define MAX_SPEED  4  // 52 miliseconds per half step to achieve minimum speed of 0.2 rpm
#define MIN_SPEED  52   // 1 milisecond as maximum speed
#define SCALE 5 	   // for each 5 values in the ADC value read with 8 bit resolution, we would have one change in our speed

/* We will implement the absolut value function by using 2's complement */
unsigned char absoluteValue(unsigned char  n)
{
	n = ~n; //negation
	return n += 1;
}

interrupt VectorNumber_Vadc void ADC_ISR(void){
	range = MIN_SPEED - MAX_SPEED;
	speed = absoluteValue(ADCRL/SCALE - range);
	ADC_value=ADCRL; //for debug purposes

}

interrupt 12 void MTIM(void){ //para la interrupcion 12, pag 66 manual PARA LOS LEDS
	(void) MTIMSC; //se que no lo voy a leer, (TENGO QUE LEERLO CUANDO ESTE EN 1 POR PROTOCOLO DE BORRADO)
	MTIMSC_TOF=0;// DESPUES DE LEERLO, PONERLO A 0
	//amarillo, azul-negro , cafe verde
	if(conteo==speed){
		 PTBD=arreglo_medio_paso[i];
			    i++;
			    if(i==8)
			    {
			    	i=0;
			    }
		conteo=0;
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
  //adc
  APCTL1_ADPC0=1;//pin adpc0 pa0 entrada analogica
  ADCSC1=0x60;//una conversion


  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */

  } /* loop forever */
  /* please make sure that you never leave main */
}
