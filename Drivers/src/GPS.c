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
        currentChar = gpsCharIn();
        if (currentChar == CR)
            break;

        command[i] = currentChar;
    }
}

//Calculating the distance in Km, The values need to be in Radian
double calculateDistance(geoPoint_t currPoint, geoPoint_t destiation)
{
    double currLat = DEG_TO_RAD(currPoint.latitude_d) / 100.0;
    double currlon = DEG_TO_RAD(currPoint.longitude_d) / 100.0;

    double x = sin(currLat) * sin(destiation.latitude_d);
    double y = cos(currLat) * cos(destiation.latitude_d);

    return acos(x + y * cos(destiation.longitude_d - currlon)) * EARTH_RADIUS;
}


bool get_current_position(char *command, geoPoint_t *currPosition)
{
    char *token, *latitude, *longitude, *arr[6], *ptr;
    const char *deli = ",";
    int tokenIndex = 0;

    // Skip garbage characters before the start marker
    char *start = strstr(command, GPRMC);
    if (start == NULL)
        return false;

    command = start;

    // We start tokenizing our command
    token = strtok(command, deli);

    while (token != NULL && tokenIndex < 6)
    {
        arr[tokenIndex++] = token;
        token = strtok(NULL, deli);
    }

    // We check if our signal is active
    if (*arr[2] != ACTIVE)
        return false;

    // Stroing the data in our struct in double
    currPosition->latitude_d = strtod(arr[3], &ptr);
    currPosition->longitude_d = strtod(arr[5], &ptr);

    return true;
}
