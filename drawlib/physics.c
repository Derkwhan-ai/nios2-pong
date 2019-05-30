#include "physics.h"


short int collisionRect(RECTANGLE r1, RECTANGLE r2) {
	if (
		r1.x <= r2.x + r2.width &&
		r1.x + r1.width >= r2.x &&
		r1.y <= r2.y + r2.height &&
		r1.y + r1.height >= r2.y
	) {
		if (r1.x + r1.width - 1 <= r2.x) return 1;
		if (r1.x >= r2.x + r2.width - 1) return -1;
		if (r1.y + r1.height - 1 <= r2.y) return 2;
		if (r1.y >= r2.y + r2.height - 1) return -2;

		return 3;
	}

	return 0;
}

void fixCollisionPosition(RECTANGLE *s, RECTANGLE *e) {
	// s = solid, won't move
	// e = elastic, will be repositioned

	if (s->x + s->width > e->x && s->x + s->width < e->x + e->width) {
		e->x = s->x + s->width + 1;
	} else if (s->x < e->x + e->width && s->x > e->x) {
		e->x = s->x - e->width - 1;
	}

	if (s->y + s->height > e->y && s->y + s->height < e->y + e->height) {
		e->y = s->y + s->height + 1;
	} else if (s->y < e->y + e->height && s->y > e->y) {
		e->y = s->y - e->height - 1;
	}
}

short int collisionScreenRect(RECTANGLE r) {
	if (r.x <= 0) return -1;
	if (r.y <= 0) return -2;
	if ((r.x + r.width) >= SCREEN_WIDTH - 1) return 1;
	if ((r.y + r.height) >= SCREEN_HEIGHT - 1) return 2;

	return 0;
}
