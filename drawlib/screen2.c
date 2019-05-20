#include "screen.h"

void initScreen() {
    // prepare screen to print the game
}

void drawPixel(int x, int y, COLOR color) {
    // draw a pixel in x, y position with a color
    // x in [0, SCREEN_MAX_WIDTH] (SCREEN_WIDTH is also defined)
    // y in [0, SCREEN_MAX_HEIGHT] (SCREEN_HEIGHT is also defined)
}

void waitScreen() {
    // waits for screen vertical retrace
}

// Avoid this.
void clearScreen() {
    // This does nothing
}
