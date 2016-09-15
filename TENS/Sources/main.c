#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
unsigned int tiempo_operacion;
unsigned int frecuencia;
 void delay (unsigned int tiempo)
 {
	 do{
		 SRTISC=0b00000111;//rti cuenta cada segundo 
		 do{
			 __RESET_WATCHDOG();	/* feeds the dog */
		 }while(SRTISC_RTIF==0); // polling
	 }while(--tiempo); 
	 SRTISC=0b00000000; //DETENER
 }
 

void estimulo (unsigned int frecuencia)
{
	unsigned int medio_periodo;
	TPMSC=0x0f; /// tpm con prescaler de 128 cuenta cada 32 microsegundos , interrupciones apagadas para trabajarcon polling
	TPMC0SC=0x14; /// outpit compare con toggle
	if(frecuencia==1)//1 hz    /// T= 1 segundo
	{
		medio_periodo=15625;   //T/2= mitad del periodo      mitad/32us= cuanto voy a contar  
	}
	else if(frecuencia==5)//5hz T= 200 ms
	{
		medio_periodo=3125;
	}
	else if(frecuencia==10)//10hz  T=100 ms
	{
		medio_periodo=1562;
	}
	else if(frecuencia==50)//50hz  T=20 ms
	{
		medio_periodo=312;
	}
	else if(frecuencia==100)//100hz T=10 ms
	{
		medio_periodo=156;
	}
	else if(frecuencia==200)//200hz  T= 5ms.
	{
		medio_periodo=78;
	}
	else//default 1 hz
	{
		medio_periodo=15625;
	}
	TPMC0V=TPMCNT+medio_periodo;
    do{
    	__RESET_WATCHDOG();	/* feeds the dog */
    }while (TPMC0SC_CH0F==0); //polling
    (void)TPMC0SC;
    TPMC0SC_CH0F=0;//limpiar bandera
    TPMC0V+=medio_periodo; // sumas la mitad del periodo para hacer toggle
	
}
void apagar_TPM(void)
{
	TPMC0SC=0x18; // apagas tpm con clear
}

void main(void) {
  EnableInterrupts;
  /* include your code here */
  PTADD_PTADD0=1;//saldia ch0 ptb 0-2 frecuencia, ptb 3-4segundos de operacion ,ptb 5 reposo, ptb6 es el on/off
  PTBPE=0x7F;//resistencia pull up
  

  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */
    if(PTBD_PTBD6){ // si esta prendido
    	if(PTBD_PTBD2==0&&PTBD_PTBD1==0&&PTBD_PTBD0==0){
    		frecuencia =1;
    	}
    	else if(PTBD_PTBD2==0&&PTBD_PTBD1==0&&PTBD_PTBD0==1)
    	{
    		frecuencia =5;
    	}
    	else if(PTBD_PTBD2==0&&PTBD_PTBD1==1&&PTBD_PTBD0==0)
    	{
    		frecuencia =10;
      	}
    	else if(PTBD_PTBD2==0&&PTBD_PTBD1==1&&PTBD_PTBD0==1)
    	{
    		frecuencia =50;
      	}	
    	else if(PTBD_PTBD2==1&&PTBD_PTBD1==0&&PTBD_PTBD0==0)
    	{
    		frecuencia =100;
      	}	
    	else if(PTBD_PTBD2==1&&PTBD_PTBD1==0&&PTBD_PTBD0==1)
    	{
    		frecuencia =200;
      	}	
    	else 
    	{
    		frecuencia =1;	
      	}	
    	estimulo(frecuencia);  /// iniciar tpm
    	if(PTBD_PTBD4==0&&PTBD_PTBD3==1)
    	{
    		tiempo_operacion=1;
    	}
    	else if (PTBD_PTBD4==1&&PTBD_PTBD3==0)
    	{
    		tiempo_operacion=2;
    	}
    	else if (PTBD_PTBD4==1&&PTBD_PTBD3==1)
    	{
    		tiempo_operacion=3;
    	}
    	else //default 4
    	{
    		tiempo_operacion=4;
    	}
    	delay(tiempo_operacion); /// no hacer nada 
    	apagar_TPM(); // clear al tpm
    	if(PTBD_PTBD5) // tiempo de reposo
    	{
    		delay(1);
    	}
    	else
    	{
    		delay(2);
    	}	
    	
    }
  } /* loop forever */
  /* please make sure that you never leave main */
}
