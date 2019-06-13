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


volatile short int* screen = (short int*) 0x08000000;
volatile int* buffer = (int *) 0x10003020;
volatile int* status = (int*) 0x1000302C;

void initScreen() {
    // prepare screen to print the game
    // This can be empty.
}

void drawPixel(int x, int y, COLOR color) {
    // draw a pixel in x, y position with a color
    // x in [0, SCREEN_MAX_WIDTH]
    // y in [0, SCREEN_MAX_HEIGHT]

    if (x < 0 && x > SCREEN_MAX_WIDTH) {
		return;
	}
	if (y < 0 && y > SCREEN_MAX_HEIGHT) {
		return;
	}

	*(screen + y * 512 + x) = color;
}

void waitScreen() {
    // waits for screen vertical retrace
    *buffer = 1;
	while (((*status) & 0x1) == 1);
}

void clearScreenSoft() {
	return;
}

// Avoid this.
void clearScreen() {
    // This should do nothing
    // clearScreen is required when using SFML

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			*(screen + y * 512 + x) = COLOR_BLACK;
		}
	}
}

void updateScreen() {
	// Only for SFML
}
