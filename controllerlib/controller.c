#include <SFML/Graphics.hpp>
#include "controller.h"

sf::Event event;

char switches[18];
char buttons[3];

char controllerMaintain() {
    char hasMorePending = screen_window.pollEvent(event);

    if (hasMorePending) {

        if (event.type == sf::Event::Closed) {
            printf("Event: closed window\n");
            screen_window.close();
            return 2;
        }

        if (event.type == sf::Event::KeyPressed) {
            //printf("Event: KeyPressed %d\n", event.key.code);

            switch(event.key.code) {
                case 22: // W key
                switches[17] = 1;
                break;

                case 73: // Up arrow
                switches[0] = 1;
                break;

                case 58: // Enter key
                buttons[0] = 1;
                break;

                case 27: // Top 1 key
                buttons[2] = 1;
                break;

                case 28: // Top 2 key
                buttons[1] = 1;
                break;

                case 29: // Top 3 key
                buttons[0] = 1;
                break;

                default:
                break;
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            //printf("Event: KeyReleased %d\n", event.key.code);

            switch(event.key.code) {
                case 22: // W key
                switches[17] = 0;
                break;

                case 73: // Up arrow
                switches[0] = 0;
                break;

                case 58: // Enter key
                buttons[0] = 0;
                break;

                case 27: // Top 1 key
                buttons[2] = 0;
                break;

                case 28: // Top 2 key
                buttons[1] = 0;
                break;

                case 29: // Top 3 key
                buttons[0] = 0;
                break;

                default:
                break;
            }
        }
    }

    return hasMorePending;
}

char getSwitchValue(char n) { // return the n-th switch value (0 or 1)
    unsigned short cmReturn;

    do {
        cmReturn = controllerMaintain();
    } while(cmReturn == 1);

    return switches[(short int) n];
}


char getButtonValue(char n) { // return the n-th button balue (0 or 1)
    unsigned short cmReturn;

    do {
        cmReturn = controllerMaintain();
    } while(cmReturn == 1);
    
    return buttons[(short int) n];
}


void setGreenLed(char n, char state) { // set the on-off state of the n-th green led
    return;
}

void setRedLed(char n, char state) { // set the on-off state of the n-th red led
    return;
}


void setSegDisplay1(int value) {
    return;
}

void setSegDisplay2(int value) {
    return;
}


void printLCD(char* str) { // prints the char buffer to the lcd screen. CAUTION: mind the line breaks and screen boundaries!
    return;
}
void moveLCDCursor(char x, char y) { // set the x and y position o the LCD cursor.
    return;
}

void audio_output(int* audio, int lenght) {
    return;
}
