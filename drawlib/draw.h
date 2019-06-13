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

typedef struct ellipse {
    int x, y;
    int width, height;
    COLOR color;
} ELLIPSE;


void drawLine(LINE);
void clearLine(LINE);

void drawRect(RECTANGLE);
void clearRect(RECTANGLE);


void drawImage(const unsigned short* img, short x, short y, short w, short h);

#endif
