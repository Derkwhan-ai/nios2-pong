#include <SFML/Graphics.hpp>
#include "drawlib.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_SCALE 2

sf::RenderWindow window;


int collisionRect(RECTANGLE r1, RECTANGLE r2) {
	if (
		r1.x < r2.x + r2.width &&
		r1.x + r1.width > r2.x &&
		r1.y < r2.y + r2.height &&
		r1.height + r1.y > r2.y
	) {
		if (r1.x + r1.width - 1 == r2.x) return 1;
		if (r1.x == r2.x + r2.width - 1) return -1;
		if (r1.y + r1.height - 1 == r2.y) return 2;
		if (r1.y == r2.y + r2.height - 1) return -2;

		return 3;
	}

	return 0;
}

int collisionRectElipse(RECTANGLE r1, ELIPSE r2) {
	if (
		r1.x < r2.x + r2.width &&
		r1.x + r1.width > r2.x &&
		r1.y < r2.y + r2.height &&
		r1.height + r1.y > r2.y
	) {
		if (r1.x + r1.width - 1 == r2.x) return 1;
		if (r1.x == r2.x + r2.width - 1) return -1;
		if (r1.y + r1.height - 1 == r2.y) return 2;
		if (r1.y == r2.y + r2.height - 1) return -2;
	}

	return 0;
}

int collisionScreenRect(RECTANGLE r) {
	if (r.x <= 0) return -1;
	if (r.y <= 0) return -2;
	if ((r.x + r.width) >= SCREEN_WIDTH - 1) return 1;
	if ((r.y + r.height) >= SCREEN_HEIGHT - 1) return 2;

	return 0;
}

int collisionScreenElipse(ELIPSE r) {
	if (r.x <= 0) return -1;
	if (r.y <= 0) return -2;
	if ((r.x + r.width) >= SCREEN_WIDTH - 1) return 1;
	if ((r.y + r.height) >= SCREEN_HEIGHT - 1) return 2;

	return 0;
}



void initScreen() {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	window.create(sf::VideoMode(SCREEN_WIDTH*SCREEN_SCALE, SCREEN_HEIGHT*SCREEN_SCALE, desktop.bitsPerPixel), "Pong");
	// window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	clearScreen();
}

void updateScreen() {
	window.display();
}

void waitScreen() {
	return;
}

sf::Color colorToSFML(short int color) {
	short int r = (color & 0xFC00) >> 11;
	short int g = (color & 0x7E0) >> 5;
	short int b = (color & 0x1F) >> 0;

	r = ((float) r / 0x1F) * 255;
	g = ((float) g / 0x3F) * 255;
	b = ((float) b / 0x1F) * 255;

	return sf::Color(r, g, b);
}


void drawPixel(int x, int y, COLOR color) {
	sf::RectangleShape rectangle(sf::Vector2f(SCREEN_SCALE, SCREEN_SCALE));

	rectangle.setPosition(x*SCREEN_SCALE, y*SCREEN_SCALE);
	rectangle.setFillColor(colorToSFML(color));

	window.draw(rectangle);
}


// Avoid this.
void clearScreen() {
	window.clear(sf::Color::Black);
}


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
	for(int y = rect.y; y <= rect.y + rect.height; y++) {
		drawPixel(rect.x, y, rect.color);
	}
	for(int y = rect.y; y <= rect.y + rect.height; y++) {
		drawPixel(rect.x + rect.width, y, rect.color);
	}
	for(int x = rect.x + 1; x <= rect.x + rect.width - 1; x++) {
		drawPixel(x, rect.y, rect.color);
	}
	for(int x = rect.x + 1; x <= rect.x + rect.width - 1; x++) {
		drawPixel(x, rect.y + rect.height, rect.color);
	}
}

void clearRect(RECTANGLE rect) {
	rect.color = COLOR_BLACK;
	drawRect(rect);
}

void drawRectFilled(RECTANGLE rect) {
	for(int y = rect.y; y <= rect.y + rect.height; y++) {
		for(int x = rect.x; x <= rect.x + rect.width; x++) {
			drawPixel(x, y, rect.color);
		}
	}
}

void clearRectFilled(RECTANGLE rect) {
	rect.color = COLOR_BLACK;
	drawRectFilled(rect);
}

void drawElipse(ELIPSE elipse) {
	int hh = elipse.height * elipse.height;
	int ww = elipse.width * elipse.width;
	int hhww = hh * ww;
	int x0 = elipse.width;
	int dx = 0;

	// do the horizontal diameter
	for (int x = -elipse.width; x <= elipse.width; x++)
	drawPixel(elipse.x + x, elipse.y, elipse.color);

	// now do both halves at the same time, away from the diameter
	for (int y = 1; y <= elipse.height; y++)
	{
		int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
		for ( ; x1 > 0; x1--)
		if (x1*x1*hh + y*y*ww <= hhww)
		break;
		dx = x0 - x1;  // current approximation of the slope
		x0 = x1;

		for (int x = -x0; x <= x0; x++)
		{
			drawPixel(elipse.x + x, elipse.y - y, elipse.color);
			drawPixel(elipse.x + x, elipse.y + y, elipse.color);
		}
	}
}

void clearElipse(ELIPSE elipse) {
	elipse.color = COLOR_BLACK;
	drawElipse(elipse);
}
