#include "GPS.h"


//initialization of the GPS on UART1 with BaudRate of 9600 on 16MHZ clock 
void gps_init(unsigned clk, unsigned baudrate)
{
    unsigned BRD;
    SYSCTL_RCGCUART_R |= 0x02; // enable clk of UART1
    SYSCTL_RCGCGPIO_R |= 0x02; // enable clk of PORTB
    UART1_CTL_R &= ~(0x01);    // disable UART1 during initialisation
    BRD = ((clk << 2) + (baudrate << 1)) / baudrate;
    UART1_IBRD_R = BRD >> 6;
    UART1_FBRD_R = BRD & 64;
    UART1_LCRH_R = 0x60;  // disable fifo , 1stop bit , no parity ,8 data bits
    UART1_CTL_R |= 0x301; // Enable Uart,RXE,TXE
    //////////////////////////PORTB_UART_PINS_INITIALISATION
    GPIO_PORTB_AFSEL_R |= 0x03;  // Turn on alternate function to pin B0,B1
    GPIO_PORTB_PCTL_R = 0x011;   // Select UART1 for PB0,PB1
    GPIO_PORTB_DEN_R |= 0x03;    // Enable digital
    GPIO_PORTB_AMSEL_R &= ~0x03; // Disable analog
}

void gpsOutChar(char data)
{
    while ((UART1_FR_R & TxFullFlag) != 0)
    {
    } // wait if TxFF is set (fifo is full)
    UART1_DR_R = data;
}
char gpsCharIn(void)
{
    while ((UART1_FR_R & RxEmptyFlag) != 0)
    {
    } // wait if RxFE is set (fifo is empty)
    return (char)UART1_DR_R;
}


void gpsGetCommand(char *command, int length)
{
    int i;
    char currentChar;
    for (i = 0; i < length; i++)
    {
        currentChar = gpsCharIn();// Get a single character from UART1
        if (currentChar == CR) // Stop reading if the carriage return character is received
            break;

        command[i] = currentChar;// Store the received character in the buffer
    }
}

// Function to calculate the distance between two geo points in meters
// The values need to be in Radian
float calculateDistance(geoPoint_t currPoint, geoPoint_t destiation)
{
	float currLat = DEG_TO_RAD(currPoint.latitude_d);
    float currlon = DEG_TO_RAD(currPoint.longitude_d);
    float dLat = destiation.latitude_d - currLat;
    float dLon = destiation.longitude_d - currlon;

    float a = sin(dLat / 2) * sin(dLat / 2) +
              cos(currLat) * cos(destiation.latitude_d) *
                  sin(dLon / 2) * sin(dLon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    float distance = EARTH_RADIUS * c;
    return distance;
}



bool get_current_position(char *command, geoPoint_t *currPosition)
{
    char *token, *latitude, *longitude, *arr[6], *ptr;
    const char *deli = ",";
    int tokenIndex = 0;

    // Skip garbage characters before the start marker
    char *start = strstr(command, GPRMC);
    
		// Return false if the start marker ("GPRMC") is not found in the reading of Gps
		if (start == NULL)
        return false;

    command = start;

    // Tokenize the command using the comma as a delimiter
    token = strtok(command, deli);

    while (token != NULL && tokenIndex < 6)
    {
        arr[tokenIndex++] = token;
        token = strtok(NULL, deli);
    }

    // Check if the signal is active
    if (*arr[2] != ACTIVE)
        return false;

    // Stroing the data in our struct in double
     currPosition->latitude_d = toDecimalDeg(arr[3]);
    currPosition->longitude_d = toDecimalDeg(arr[5]);


    return true; // Return true if the current position was successfully obtained
}


//Getting the destination lat and long from the laptop through UART
geoPoint_t getDestination()
{
		char lat[10], lon[10];	
		geoPoint_t dest;
		
		UART0_clearScreen();
		UART0_writestring("Enter the destination latitude: ");
		UART0_readstring(lat, CR);
		UART0_clearScreen();
		
		UART0_writestring("Enter the destination longitude: ");
		UART0_readstring(lon, CR);
		UART0_clearScreen();
		
		dest.latitude_d = DEG_TO_RAD(atof(lat));
		dest.longitude_d = DEG_TO_RAD(atof(lon));
		 
		return dest;
}

float toDecimalDeg(char *gpsReading)
{
    float floatReading = atof(gpsReading) / 100;
    int integerPart = (int)(floatReading);
    float decimalPart = (floatReading - integerPart) * 100 / 60.0;

    return (integerPart + decimalPart);
}
	
