#ifndef STATES_H
#define STATES_H

#include "GPS.h"
#include "GPIO_init.h"
#include "uart.h"
#include "SysTick.h"
#include "lcd.h"

#define MAX_ALLOWED_ERRORS 10

void locatingSatellite(char* command, geoPoint_t* currPosition);
void readyState();
bool getStartingPosition(char* command, geoPoint_t* currPosition);
void errorState();
void reachingState();
void destiationIsFar();
void destinationReached();

#endif