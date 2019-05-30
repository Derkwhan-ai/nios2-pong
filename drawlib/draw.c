#include "draw.h"

void drawLine(LINE line) {
	int dx = abs(line.x2 - line.x1);
	int sx = line.x1 < line.x2 ? 1 : -1;

	int dy = abs(line.y2 - line.y1);
	int sy = line.y1 < line.y2 ? 1 : -1;

	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	for(;;){
		drawPixel(line.x1, line.y1, line.color);

		if (line.x1 == line.x2 && line.y1 == line.y2) break;

		e2 = err;

		if (e2 >-dx) {
			err -= dy;
			line.x1 += sx;
		}

		if (e2 < dy) {
			err += dx;
			line.y1 += sy;
		}
	}
}

void clearLine(LINE line) {
	line.color = COLOR_BLACK;
	drawLine(line);
}

void drawRect(RECTANGLE rect) {
	for(int y = floor(rect.y); y <= floor(rect.y + rect.height); y++) {
		drawPixel(rect.x, y, rect.color);
	}
	for(int y = floor(rect.y); y <= floor(rect.y + rect.height); y++) {
		drawPixel(rect.x + rect.width, y, rect.color);
	}
	for(int x = rect.x + 1; x < floor(rect.x + rect.width); x++) {
		drawPixel(x, floor(rect.y), rect.color);
	}
	for(int x = rect.x + 1; x < floor(rect.x + rect.width); x++) {
		drawPixel(x, floor(rect.y) + rect.height, rect.color);
	}
}

void clearRect(RECTANGLE rect) {
	rect.color = COLOR_BLACK;
	drawRect(rect);
}

void drawRectFilled(RECTANGLE rect) {
	for(int y = floor(rect.y); y <= floor(rect.y + rect.height); y++) {
		for(int x = floor(rect.x); x <= floor(rect.x + rect.width); x++) {
			drawPixel(x, y, rect.color);
		}
	}
}

void clearRectFilled(RECTANGLE rect) {
	rect.color = COLOR_BLACK;
	drawRectFilled(rect);
}
