#ifndef STATES_H
#define STATES_H

#include "GPS.h"
#include "GPIO_init.h"
#include "uart.h"
#include "SysTick.h"
#include "lcd.h"


void locatingSatellite(char* command, geoPoint_t* currPosition);
void readyState();

#endif