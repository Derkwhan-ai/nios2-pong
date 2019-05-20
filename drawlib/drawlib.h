#ifndef _DRAWLIB_
#define _DRAWLIB_

#define COLOR_RED (short int) 0xF800
#define COLOR_BLUE (short int) 0x1F
#define COLOR_GREEN (short int) 0x7E0
#define COLOR_BLACK (short int) 0x0
#define COLOR_WHITE (short int) 0xFFFF

typedef short int COLOR;

typedef struct line {
    int x1, y1;
    int x2, y2;
    COLOR color;
} LINE;

typedef struct rectangle {
    int x, y;
    int width, height;
    COLOR color;
} RECTANGLE;

typedef struct elipse {
    int x, y;
    int width;
    int height;
    COLOR color;
} ELIPSE;


void waitScreen();

// Avoid this.
void clearScreen();

void drawPixel(int, int, COLOR);

void drawLine(LINE);
void clearLine(LINE);

void drawRect(RECTANGLE);
void clearRect(RECTANGLE);

void drawElipse(ELIPSE);
void clearElipse(ELIPSE);


#endif
