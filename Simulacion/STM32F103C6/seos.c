#include <stm32f103x6.h>
#include <seos.h>



#include <stdlib.h>
#include <string.h>

#include "tc72.h"

volatile unsigned char Flag=0;

//Funcion privada de libreria
//(para no hacer otra libreria con solo esta función, meto la task acá)
void seos_FormatTemp (void);

void SEOS_Init(){
	//configuro SysTick para interrupciones cada 100 ms
	//SysTick->LOAD = 7199999UL; //T=100ms para fclk=72MHz, 
	//SysTick->LOAD = 799999UL; //T=100ms para fclk = 8MHz, 
	SysTick->LOAD = 1599999UL; //T= 200ms para fclk=8MHz
	SysTick->CTRL = 0x3;
}

void SEOS_Dispatch_Tasks(){
	
	if(Flag==1){ //Esto corre cada 200ms
		seos_FormatTemp();
		Flag=0;
	}	
}

void SysTick_Handler() //Esto corre cada 200ms
{
	Flag=1;
}

void seos_FormatTemp () {
	unsigned char* temp= TC72getTemperature();
	LCDGotoXY(4,1);
	LCDstring(temp,7);
}
