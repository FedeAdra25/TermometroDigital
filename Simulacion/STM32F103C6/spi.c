#include <spi.h>
#include <stdint.h.>


void spi_init () {
   //Habilito el reloj en el periferico
   RCC -> APB2ENR |= 0xFC | (1<<12) ; 
   //Bit 7 y 5 del registro A como salida alternativa, el 6 como entrada 
   GPIOA-> CRL = 0xB4B34444;
   //Configuro un baudrate de 4 (divido la frecuencia por 16 ya que maf freq del TC72 = 7,5 Mhz ), enciendo el dispositivo, y formato de datos 0 (8 bits) 
   //SPI1 -> CR1 = 0x364;
   SPI1 -> CR1 = 0x35D;
   GPIOA->BSRR = (1<<4);
   spi_transfer(0x80); 
   spi_transfer(0x04); 
   GPIOA->BRR = (1<<4);
}

uint8_t spi_transfer (uint8_t data) {
   SPI1 -> DR = data ;//envio el contenido de d
   while ((SPI1-> SR & (1<<0)) == 0); //espero a que se termine la transferencia
   return SPI1 -> DR; //retorno el valor recibido
}

uint16_t spi_receive () {
   uint16_t res = 0;
   uint8_t ent =0;
   uint8_t dec = 0;
   GPIOA->BSRR = (1<<4);
   spi_transfer(0x02);
   ent = spi_transfer(0);
   dec = spi_transfer(0); // Transamito basura, solo sirve para leer el registro
   spi_transfer(0);
   GPIOA->BRR = (1<<4);
   res = 256U * ent + dec;
   return res;
}

uint8_t spi_receiveHigh () {
   uint8_t data = 0;
   GPIOA->BSRR = (1<<4);
   spi_transfer(0x02);
   data= spi_transfer(0);
   GPIOA->BRR = (1<<4);
   return data;
   
}

uint8_t spi_receiveLow () {
   uint8_t data = 0;
   GPIOA->BSRR = (1<<4);
   spi_transfer(0x01);
   data= spi_transfer(0);
   GPIOA->BRR = (1<<4);
   return data;
}

