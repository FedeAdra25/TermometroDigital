#ifndef UTILS_H_
#define UTILS_H_
#include <stm32f103x6.h>
#ifndef F_CPU
#define F_CPU 8000000
#endif

#define CONST_FOR_US_DELAY 12
#define CONST_FOR_MS_DELAY 6000

void delay_ms(unsigned long);
void delay_us(unsigned long);
#endif
