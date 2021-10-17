#ifndef SPI_H
#define SPI_H

#include <stdint.h.>
#include <stm32f103x6.h>
#include <utils.h.>

void spi_init (void);
uint8_t spi_transfer (uint8_t );
uint16_t spi_receive (void);
uint8_t spi_receiveHigh (void) ;
uint8_t spi_receiveLow (void) ;

#endif
