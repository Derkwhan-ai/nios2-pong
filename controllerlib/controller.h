#ifndef _CONTROLLERLIB_
#define _CONTROLLERLIB_


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
