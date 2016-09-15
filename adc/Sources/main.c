#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
unsigned char ADC_value[3];
unsigned char ADC_sel[]={0xC0,0x63,0x66};
unsigned char i;
unsigned char ADC_str[]={" .   V"};
interrupt VectorNumber_Vadc void ADC_ISR(void){
unsigned int temp;
	temp=((unsigned int)ADCRL*3300)/255;
	ADC_str[4]=temp%10+ 0x30;
	temp/=10;
	ADC_str[3]=temp%10+ 0x30;
	temp/=10;
	ADC_str[2]=temp%10+ 0x30;
	temp/=10;
	ADC_str[0]=temp/10+ 0x30;
	ADC_value[i++]=ADCRL;
	if(i==3)
	{
		i=0;
	}
}
interrupt VectorNumber_Vmtim  void MTIM_ISR(void){ //para la interrupcion 12, pag 66 manual PARA LOS LEDS
	(void) MTIMSC; //se que no lo voy a leer, (TENGO QUE LEERLO CUANDO ESTE EN 1 POR PROTOCOLO DE BORRADO)
	MTIMSC_TOF=0;// DESPUES DE LEERLO, PONERLO A 0
	ADCSC1=ADC_sel[i];

}
void main(void) {
  EnableInterrupts;
  /* include your code here */
  APCTL1_ADPC0=1;//pin adpc0 pa0 entrada analogica 
  APCTL1_ADPC3=1;//pa3
  APCTL1_ADPC6=1;//pb2
  //APCTL1_ADPC=0x49;
  ADCSC1=0x40;//una conversion
  
//base de tiempo 1 ms 
  MTIMSC=0x40;
  MTIMCLK=0x04;
  MTIMMOD=250;

  i=0;
  for(;;) {
   
    
    do {
    	__RESET_WATCHDOG();	/* feeds the dog */
    }while(1);
  } /* loop forever */
  /* please make sure that you never leave main */
}
