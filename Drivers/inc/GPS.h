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
#define BUFFER_SIZE 128	// The size of the buffer used for storing GPS Readings

#define DEG_TO_RAD(DEG) ((DEG * PI / 180)) // Macro to convert degrees to radians
#define GPRMC "GPRMC" // The start marker for the GPS command we are interested in
#define ACTIVE 'A'	// The character indicating an active(Valid) GPS signal

#define RxEmptyFlag 0x10 // The receive buffer empty flag mask
#define TxFullFlag 0x20 // The transmit buffer full flag mask
#define CR 0x0D	// The carriage return character(\r)

// Struct to store a GPS coordinate as a latitude and longitude in decimal degrees
typedef struct
{
    double latitude_d;
    double longitude_d;
} geoPoint_t;

// Function prototypes
void gps_init(unsigned clk, unsigned baudrate);
void gpsOutChar(char data);
char gpsCharIn(void);
void gpsGetCommand(char *command, int length);
bool get_current_position(char *command, geoPoint_t *currPosition);
double calculateDistance(geoPoint_t currPoint, geoPoint_t destiation);
#endif
