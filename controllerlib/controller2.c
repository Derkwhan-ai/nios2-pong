#include "controller.h"

volatile long int* slider = (long int *) 0x10000040;
volatile long int* led_red = (long int *) 0x10000000;
volatile int* led_green = (int *) 0x10000010;
volatile int* display1 = (int *) 0x10000020;
volatile int* display2 = (int *) 0x10000030;

char controllerMaintain() {
    // This can be empty
    return 0;
}

char getSwitchValue(char n) { // return the n-th switch value (0 or 1)
    if (n < 0 or n > 17) return 0;
    
    return (*slider) & (1 << n);
}


char getButtonValue(char n) { // return the n-th button balue (0 or 1)
    return 0;
}


void setGreenLed(char n, char state) { // set the on-off state of the n-th green led

}

void setRedLed(char n, char state) { // set the on-off state of the n-th red led

}


void setSegDisplay(char n, char c) { // set the displayed digit of the n-th 7-segment display

}


void printLCD(char* str) { // prints the char buffer to the lcd screen. CAUTION: mind the line breaks and screen boundaries!

}
void moveLCDCursor(char x, char y) { // set the x and y position o the LCD cursor.

}
