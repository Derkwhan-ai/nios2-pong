#ifndef _DRAW_
#define _DRAW_


typedef struct line {
    float x1, y1;
    float x2, y2;
    COLOR color;
} LINE;

typedef struct rectangle {
    float x, y;
    float width, height;
    COLOR color;
} RECTANGLE;


void drawLine(LINE);
void clearLine(LINE);

void drawRect(RECTANGLE);
void clearRect(RECTANGLE);


#endif
