#include <SFML/Graphics.hpp>
#include "screen.h"

sf::RenderWindow screen_window;

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

	screen_window.draw(rectangle);
}


// Avoid this.
void clearScreen() {
	screen_window.clear(sf::Color::Black);
}

void waitScreen() {
	return;
}


void initScreen() {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	screen_window.create(sf::VideoMode(SCREEN_WIDTH*SCREEN_SCALE, SCREEN_HEIGHT*SCREEN_SCALE, desktop.bitsPerPixel), "Pong");
	// window.setVerticalSyncEnabled(true);
	screen_window.setFramerateLimit(60);

	clearScreen();
}

void updateScreen() {
	screen_window.display();
}
