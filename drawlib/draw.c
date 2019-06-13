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
	for(int y = (int) (rect.y); y <= (int) (rect.y + rect.height); y++) {
		drawPixel(rect.x, y, rect.color);
	}
	for(int y = (int) (rect.y); y <= (int) (rect.y + rect.height); y++) {
		drawPixel(rect.x + rect.width, y, rect.color);
	}
	for(int x = rect.x + 1; x < (int) (rect.x + rect.width); x++) {
		drawPixel(x, (int) (rect.y), rect.color);
	}
	for(int x = rect.x + 1; x < (int) (rect.x + rect.width); x++) {
		drawPixel(x, (int) (rect.y) + rect.height, rect.color);
	}
}

void clearRect(RECTANGLE rect) {
	rect.color = COLOR_BLACK;
	drawRect(rect);
}

void drawRectFilled(RECTANGLE rect) {
	for(int y = (int) (rect.y); y <= (int) (rect.y + rect.height); y++) {
		for(int x = (int) (rect.x); x <= (int) (rect.x + rect.width); x++) {
			drawPixel(x, y, rect.color);
		}
	}
}

void clearRectFilled(RECTANGLE rect) {
	rect.color = COLOR_BLACK;
	drawRectFilled(rect);
}

void drawEllipse(ELLIPSE e) {
    int rx = e.width / 2;
    int ry = e.height / 2;
    int xc = e.x + e.width / 2;
    int yc = e.y + e.height / 2;

    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // Initial decision parameter of region 1
    d1 = (ry * ry)
         - (rx * rx * ry)
         + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1
    while (dx < dy) {

        // Print points based on 4-way symmetry
        drawPixel(x + xc, y + yc, e.color);
        drawPixel(-x + xc, y + yc, e.color);
        drawPixel(x + xc, -y + yc, e.color);
        drawPixel(-x + xc, -y + yc, e.color);

        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5)))
         + ((rx * rx) * ((y - 1) * (y - 1)))
         - (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0) {

        // printing points based on 4-way symmetry
        drawPixel(x + xc, y + yc, e.color);
        drawPixel(-x + xc, y + yc, e.color);
        drawPixel(x + xc, -y + yc, e.color);
        drawPixel(-x + xc, -y + yc, e.color);

        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

void clearEllipse(ELLIPSE e) {
	e.color = COLOR_BLACK;
	drawEllipse(e);
}

void drawImage(const unsigned short* img, short xi, short yi, short w, short h) {
	for (short y = 0; y < h; y++) {
		for (short x = 0; x < w; x++) {
			drawPixel(xi + x, yi + y, *(img + w * y + x));
		}
	}
}
