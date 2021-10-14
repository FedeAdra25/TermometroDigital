#include <spi.h>

void spi_init () {
   //Habilito el reloj en el periferico
   RCC -> APB2ENR |= 0xFC | (1<<12) ; 
   //Bit 7 y 5 del registro A como salida alternativa, el 6 como entrada 
   GPIOA-> CRL = 0xB4B34444;
   //Configuro un baudrate de 3 (divido la frecuencia por 8), enciendo el dispositivo, y formato de datos 0 (8 bits) 
   SPI1 -> CR1 = 0x35C;
}

uint8_t spi_transfer (uint8_t data) {
   SPI1 -> DR = data ;//envio el contenido de d
   while ((SPI1-> SR & (1<<0)) == 0); //espero a que se termine la transferencia
   return SPI1 -> DR; //retorno el valor recibido
}

uint16_t spi_receive () {
   uint16_t data = 0;
   uint8_t aux = 0;
   GPIOA->BRR = (1<<4);
   spi_transfer(0x02h); //Transmito la direccion 2 hexa indicando que voy a leer los datos de ahi
   aux = spi_transfer(0); // Transamito basura, solo sirve para leer el registro
   data = aux;
   aux = spi_transfer(0); // Transamito basura, solo sirve para leer el registro
   data = data + (aux >>8);
   GPIOA->BRR = (0<<4);
   return data;
}
