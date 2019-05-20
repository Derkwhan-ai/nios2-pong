#include "physics.h"


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

int collisionScreenRect(RECTANGLE r) {
	if (r.x <= 0) return -1;
	if (r.y <= 0) return -2;
	if ((r.x + r.width) >= SCREEN_WIDTH - 1) return 1;
	if ((r.y + r.height) >= SCREEN_HEIGHT - 1) return 2;

	return 0;
}
