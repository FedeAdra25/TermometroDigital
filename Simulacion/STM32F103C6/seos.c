#include <seos.h>

void seos_FormatTemp () {
   uint8_t dig = 0, dig2= 0;
   uint8_t gradosEnt = 0;
   uint8_t gradosDec = 0;
  // uint16_t temp = 0 ;
 //  temp = spi_receive() ;
   gradosEnt = spi_receiveHigh();
    if (gradosEnt > 0  && gradosEnt < 100) {
       dig = gradosEnt - (gradosEnt/10)*10 ; // dig  =  (uint8_t) gradosEnt % 10;
      gradosEnt = (uint8_t) gradosEnt / 10;
       LCDsendChar(gradosEnt+48);
       LCDsendChar(dig+48);
   }
   else {
      if (gradosEnt >= 100) {
      dig = gradosEnt - (gradosEnt/10)*10 ; // dig  =  (uint8_t) gradosEnt % 10;
      gradosEnt = (uint8_t) gradosEnt / 10;
      dig2 =  gradosEnt - (gradosEnt/10)*10 ;
       gradosEnt = (uint8_t) gradosEnt / 10;
       LCDsendChar(gradosEnt+48);
       LCDsendChar(dig2+48);
       LCDsendChar(dig+48);
      }
   }
   
   gradosDec =  spi_receiveLow();
   LCDsendChar(',');
   switch (gradosDec) {
      case 64: 
	     LCDsendChar('2');
	      LCDsendChar('5');
	 break;
      case 128:
	    LCDsendChar('5');
	     LCDsendChar('0');
	 break;
      case 192 :
	    LCDsendChar('7');
	     LCDsendChar('5');
	 break;
      default: 
	 LCDsendChar('0');
	 LCDsendChar('0');
      
   }
   
}