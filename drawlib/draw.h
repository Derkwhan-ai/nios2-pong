#ifndef _DRAW_
#define _DRAW_


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


void drawLine(LINE);
void clearLine(LINE);

void drawRect(RECTANGLE);
void clearRect(RECTANGLE);


#endif
