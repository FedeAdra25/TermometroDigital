#include "tc72.h"



//USER SHOULD NOT CHANGE THIS VARIABLE EXTERNALLY
static unsigned char temperature[7] = "+000,00";

void TC72Init(void){
	spi_init();
}

//We know this is going to execute faster than it takes to the tc72 to change temperature
//So, we read twice via SPI the temperature. Once for LSB and another one for MSB(yeah, this way we're reading twice LSB)
unsigned char * TC72getTemperature(){
		int8_t tempHigh;
		uint8_t tempLow;
		tempHigh = spi_receiveHigh();
		if(tempHigh>=0){
			temperature[0]=' ';
		}
		else{
			temperature[0]= '-';
		}	
		tempLow=spi_receiveLow();
		if(tempHigh<0){
			tempHigh=tempHigh+1;
			switch (tempLow) {
				case 64: 
					temperature[5]='7';
					temperature[6]='5';
				break;
				case 128:
					temperature[5]='5';
					temperature[6]='0';
				break;
				case 192 :
					temperature[5]='2';
					temperature[6]='5';
				break;
				default: 
					temperature[5]='0';
					temperature[6]='0';
					tempHigh=tempHigh-1;
			}
		}
		else{
			switch (tempLow) {
				case 64: 
					temperature[5]='2';
					temperature[6]='5';
				break;
				case 128:
					temperature[5]='5';
					temperature[6]='0';
				break;
				case 192 :
					temperature[5]='7';
					temperature[6]='5';
				break;
				default: 
					temperature[5]='0';
					temperature[6]='0';
			}
		}
	tempHigh = abs(tempHigh);
	temperature[1] = '0';
	temperature[2] = '0' + (tempHigh)/10; //Maldito compilador >:(
	temperature[3] = '0' + (tempHigh - (tempHigh/10)*10);
	return temperature;
}
