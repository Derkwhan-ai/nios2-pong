#include <string.h>
#include "controller.h"

volatile long int* switchReg = (long int *) 0x10000040;

volatile int* redLedReg = (int *) 0x10000000;
volatile int* greenLedReg = (int *) 0x10000010;

volatile int* display1Reg = (int *) 0x10000020;
volatile int* display2Reg = (int *) 0x10000030;

volatile char* lcdReg = (char*) 0x10003050;

volatile int* audioReg = (int*) 0x10003040;

char controllerMaintain() {
    // This can be empty
    return 0;
}

char getSwitchValue(char n) { // return the n-th switch value (0 or 1)
    if (n < 0 or n > 17) return 0;

    return ((*switchReg) & (1 << n)) >> n;
}


char getButtonValue(char n) { // return the n-th button balue (0 or 1)
    return 0;
}


void setGreenLed(char n, char state) { // set the on-off state of the n-th green led
    if (n < 0 or n > 9) return;

    if (!state) {
        *greenLedReg = *greenLedReg & ~(1 << n);
    } else {
        *greenLedReg = *greenLedReg | (1 << n);
    }
}

void setRedLed(char n, char state) { // set the on-off state of the n-th red led
    if (n < 0 or n > 18) return;

    if (!state) {
        *redLedReg = *redLedReg & ~(1 << n);
    } else {
        *redLedReg = *redLedReg | (1 << n);
    }
}


void displayOutput(int* reg, int value) {
	if (value < 0 || value > 9999) {
		return;
	}

	int display[10] = {IO_DISPLAY_0, IO_DISPLAY_1, IO_DISPLAY_2, IO_DISPLAY_3, IO_DISPLAY_4, IO_DISPLAY_5, IO_DISPLAY_6, IO_DISPLAY_7, IO_DISPLAY_8, IO_DISPLAY_9};
	int output = 0;
	int count = 0;
	int index;

	for (int i = 0, j = 1000; i < 4; i++, j /= 10) {
		index = (value - count) / j;
		count += index * j;
		output = output | (display[index] << (8 * (3 - i)));
	}

	*reg = output;
}


void setSegDisplay1(int value) {
    displayOutput(display1Reg, value);
}

void setSegDisplay2(int value) {
    displayOutput(display2Reg, value);
}


void printLCD(char* str) { // prints the char buffer to the lcd screen. CAUTION: mind the line breaks and screen boundaries!
    int length = strlen(str);

    *(lcdReg) = 0x1;

	for (int i = 0; i < length; i++) {
		*(lcdReg + 1) = str[i];
	}

	*(lcdReg) = 0xC;
}

void moveLCDCursor(char x, char y) { // set the x and y position o the LCD cursor.
    return;
}


void audio_output(int* audio, int lenght) {
    *(audioReg) = 0x8;
	*(audioReg) = 0x0;

	int wslc;
	int wsrc;

	for (int i = 0; i < lenght; i += 2) {
		do {
			wslc = (*(audioReg + 1) | 0xFF0000) >> 24;
			wsrc = (*(audioReg + 1) | 0xFF00) >> 16;
		} while ((wslc | wsrc) == 0);

		*(audioReg + 2) = audio[i];
		*(audioReg + 3) = audio[i + 1];
	}
}
