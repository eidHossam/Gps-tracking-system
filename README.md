# Gps tracking system project for introduction to embedded systems course


## Circuit Implementation

Our project consists of three main components:
1.	TM4C123GH6PM microcontroller
2.	RC1602E character LCD
3.	Ublox NEO-6m GPS Module


## Pin Configuration

GPS module PINS  | TM4C123 GPIO PINS
------------- | -------------
VCC | 3.3V
GND  | GND
TX  | PB0(uart1_RX)



|                |LCD PINS                          |TM4C123 GPIO PINS                         |
|----------------|-------------------------------|-----------------------------|
|LCD Control |RS            |PE1     |
|LCD Control |RW            |PE2            |
|LCD Control |E            |PE3          |
|LCD Data         |D7         |PD3           |
|LCD Data         |D6         |PD2           |
|LCD Data         |D5         |PD1           |
|LCD Data         |D4         |PD0           |
|Power          | VSS | GND |
|Power          | VDD | VBUS |
|Power          | VO | Potentiometer out |
|Power          | A | VBUS |
|Power          | K | GND |


## System States

The system goes through various states throughout its lifetime

* Getting the destination location through UART0 which is connected to the laptop.
    * The user enters the latitude and longitude of the desired destination.
    * "Enter the destination" on the LCD to indicate we are in this state.

*	Searching state
    *	The GPS searches for nearest satellites to read accurate locations.
    *	It usually takes around 1min and it could last longer if we were in a closed place.
    *	“Searching For satellites” on the lcd and Blue led indicate we are in the searching state.

*	Ready state
    *	We enter the Ready state after the GPS has initialized correctly and we can get readings now.
    *	We should push SW1 to exits this state and start moving.
    *	“GPS Ready Sw1 to start” on the lcd and purple led to indicate we are in the Ready state.

*	Reading state
    *	When we are moving, and the distance is being accumulated.
    *	the distance we have moved would appear on lcd.
    *   Led color depends on how far we are from the destination.

*   Destination is far state.
    * Red LED means we are more than 5 meters away from the destination.

*	Reaching state
    * Yellow LED to indicate we are less than 5 meters away from the destination.

*   Destination Reached state.
    * Green LED to indicate we reached the destination.
    * "Destination Reached" on the LCD for 5 second.
    *  The total distance we traveled is shown on the LCD then the program ends.


*	Error state
    *	White LED to indicate there is an error.
