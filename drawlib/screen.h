#ifndef _SCREEN_
#define _SCREEN_

#define COLOR_RED (short int) 0xF800
#define COLOR_BLUE (short int) 0x1F
#define COLOR_GREEN (short int) 0x7E0
#define COLOR_BLACK (short int) 0x0
#define COLOR_WHITE (short int) 0xFFFF

typedef short int COLOR;

#define SCREEN_WIDTH 320
#define SCREEN_MAX_WIDTH 319
#define SCREEN_HEIGHT 240
#define SCREEN_MAX_HEIGHT 239

#define SCREEN_SCALE 2

// extern sf::RenderWindow screen_window;

void initScreen();

void drawPixel(int x, int y, COLOR color);
void waitScreen();

// Avoid this.
void clearScreen();

void updateScreen(); // For SFML


#endif
