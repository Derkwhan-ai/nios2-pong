void drawCircle(CIRCLE c) {
	int f = 1 - c.radius;
	int ddF_x = 0;
	int ddF_y = -2 * c.radius;
	int x = 0;
	int y = c.radius;

	drawPixel(c.x, c.y + c.radius, c.color);
	drawPixel(c.x, c.y - c.radius, c.color);
	drawPixel(c.x + c.radius, c.y, c.color);
	drawPixel(c.x - c.radius, c.y, c.color);

	while(x < y)  {
		if(f >= 0)  {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;
		ddF_x += 2;
		f += ddF_x + 1;

		drawPixel(c.x + x, c.y + y, c.color);
		drawPixel(c.x - x, c.y + y, c.color);
		drawPixel(c.x + x, c.y - y, c.color);
		drawPixel(c.x - x, c.y - y, c.color);
		drawPixel(c.x + y, c.y + x, c.color);
		drawPixel(c.x - y, c.y + x, c.color);
		drawPixel(c.x + y, c.y - x, c.color);
		drawPixel(c.x - y, c.y - x, c.color);
	}
}
