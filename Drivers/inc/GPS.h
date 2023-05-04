#ifndef GPS_H
#define GPS_H

#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.141592653589793238
#define EARTH_RADIUS 6371
#define BUFFER_SIZE 128

#define DEG_TO_RAD(DEG) ((DEG * PI / 180))
#define GPRMC "GPRMC"
#define ACTIVE 'A'

#define RxEmptyFlag 0x10
#define TxFullFlag 0x20
#define CR 0x0D

typedef struct
{
    double latitude_d;
    double longitude_d;
} geoPoint_t;


void gps_init(unsigned clk, unsigned baudrate);
void gpsOutChar(char data);
char gpsCharIn(void);
void gpsGetCommand(char *command, int length);
bool get_current_position(char *command, geoPoint_t *currPosition);
double calculateDistance(geoPoint_t currPoint, geoPoint_t destiation);


void SysTick_wait(unsigned long delay);
void SysTick_wait1s(unsigned long delay);

#endif
