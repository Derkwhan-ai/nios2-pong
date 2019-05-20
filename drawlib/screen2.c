#include "screen.h"


// DEFINED WORDS:
//
// #define COLOR_RED (short int) 0xF800
// #define COLOR_BLUE (short int) 0x1F
// #define COLOR_GREEN (short int) 0x7E0
// #define COLOR_BLACK (short int) 0x0
// #define COLOR_WHITE (short int) 0xFFFF
//
// typedef short int COLOR;
//
// #define SCREEN_WIDTH 320
// #define SCREEN_MAX_WIDTH 319
// #define SCREEN_HEIGHT 240
// #define SCREEN_MAX_HEIGHT 239


void initScreen() {
    // prepare screen to print the game
}

void drawPixel(int x, int y, COLOR color) {
    // draw a pixel in x, y position with a color
    // x in [0, SCREEN_MAX_WIDTH]
    // y in [0, SCREEN_MAX_HEIGHT]
}

void waitScreen() {
    // waits for screen vertical retrace
}

// Avoid this.
void clearScreen() {
    // This does nothing
}
