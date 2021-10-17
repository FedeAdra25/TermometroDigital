#ifndef TC72_H
#define TC72_H

#include <spi.h>
#include <lcd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void TC72Init(void);

unsigned char * TC72getTemperature(void);

#endif
