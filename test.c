void drawEllipseFilled(ELLIPSE e) {
    int hh = e.height * e.height;
    int ww = e.width * e.width;
    int hhww = hh * ww;
    int x0 = width;
    int dx = 0;

    // do the horizontal diameter
    for (int x = -width; x <= width; x++)
        drawPixel(e.x + x, e.y, e.color);

    // now do both halves at the same time, away from the diameter
    for (int y = 1; y <= height; y++) {
        int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more

        for ( ; x1 > 0; x1--)
            if (x1*x1*hh + y*y*ww <= hhww)
                break;

        dx = x0 - x1;  // current approximation of the slope
        x0 = x1;

        for (int x = -x0; x <= x0; x++) {
            drawPixel(e.x + x, e.y - y, e.color);
            drawPixel(e.x + x, e.y + y, e.color);
        }
    }
}
