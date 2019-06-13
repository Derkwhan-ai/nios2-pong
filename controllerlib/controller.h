#ifndef _CONTROLLERLIB_
#define _CONTROLLERLIB_


#define IO_DISPLAY_0 0x3F
#define IO_DISPLAY_1 0x6
#define IO_DISPLAY_2 0x5B
#define IO_DISPLAY_3 0x4F
#define IO_DISPLAY_4 0x66
#define IO_DISPLAY_5 0x6D
#define IO_DISPLAY_6 0x7D
#define IO_DISPLAY_7 0x7
#define IO_DISPLAY_8 0x7F
#define IO_DISPLAY_9 0x67


char controllerMaintain();

char getSwitchValue(char); // return the n-th switch value (0 or 1)

char getButtonValue(char); // return the n-th button balue (0 or 1)

void setGreenLed(char, char); // set the on-off state of the n-th green led
void setRedLed(char, char); // set the on-off state of the n-th red led

void setSegDisplay1(int);
void setSegDisplay2(int);

void printLCD(char*); // prints the char buffer to the lcd screen. CAUTION: mind the line breaks and screen boundaries!
void moveLCDCursor(char, char); // set the x and y position o the LCD cursor.

void audio_output(int*, int); // play n samples from an audio


#endif
