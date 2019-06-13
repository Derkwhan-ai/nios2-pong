#include <stdlib.h>
#include <stdio.h>

#define BAR_STEP 2

#define PC_ENV

#ifdef NIOS_ENV
    #include "altera/exception.c"
    #include "drawlib/screen2.c"
    #include "controllerlib/controller2.c"
#else
    #include "drawlib/screen.c"
    #include "controllerlib/controller.c"
#endif

#include "drawlib/draw.c"
#include "drawlib/physics.c"

// Images assets

#include "assets/img/img_home.c"
#include "assets/img/img_credits.c"
#include "assets/img/img_instructions.c"
#include "assets/img/img_game_over_header.c"
#include "assets/img/img_game_over_p1.c"
#include "assets/img/img_game_over_p2.c"


// Env specific

#define DEBUG

#ifdef DEBUG
    #define debugPrintf(x, ...)   printf(x, ## __VA_ARGS__)
#else
    #define debugPrintf(x, ...)
#endif

void menuScreen();
void creditsScreen();
void gameScreen();
void instructionsScreen();
int main();

void menuScreen() {
    int sel = 0;

    ELLIPSE selMark = {
        65,
        0,
        10,
        10,
        COLOR_WHITE
    };

    while(1) {
        drawImage(img_home, 0, 0, 320, 240);
        updateScreen();

		while(!getButtonValue(0)) {
            if (getButtonValue(2)) {
                while(getButtonValue(2));
                sel++;
                if (sel > 2) sel = 0;
            } else if (getButtonValue(1)) {
                while(getButtonValue(1));
                sel--;
                if (sel < 0) sel = 2;
            }

            selMark.y = 145 + 28 * sel;

            drawEllipse(selMark);
			updateScreen();
			waitScreen();
			clearEllipse(selMark);
		}

		clearScreen();

		if (sel == 0) {
            gameScreen();
		} else if (sel == 1) {
            instructionsScreen();
		} else if (sel == 2) {
            creditsScreen();
		}
	}

    return;
}

void creditsScreen() {
    drawImage(img_credits, 0, 0, 320, 240);
    updateScreen();

    while(getButtonValue(0));
    while(!getButtonValue(0));
    while(getButtonValue(0));
}

void instructionsScreen() {
    drawImage(img_instructions, 0, 0, 320, 240);
    updateScreen();

    while(getButtonValue(0));
    while(!getButtonValue(0));
    while(getButtonValue(0));
}


void randomBall(RECTANGLE *ball, int *stepX, int *stepY, int ballSpeed) {
    ball->x = (SCREEN_WIDTH / 2) - (ball->width / 2);
    ball->y = rand() % (SCREEN_MAX_HEIGHT - (int) ball->height);

    *stepX = ballSpeed * 1;
    *stepY = ballSpeed * 1;

    if ((rand() % 2) > 0.5) {
        *stepX *= -1;
    }

    if ((rand() % 2) > 0.5) {
        *stepY *= -1;
    }
}

void changeAngle(RECTANGLE p, RECTANGLE b, int *stepX, int *stepY, int ballSpeed) {
    int collisionAng = (p.y - b.y + p.height - 1);

    short int dir = *stepX > 0 ? -1 : 1;

    debugPrintf("Angle: %f, Dir: %d\n", collisionAng, dir);

    if (collisionAng <= 5.375 * 1) {
        // This is the most lower section
        *stepX = ballSpeed * 3;
        *stepY = ballSpeed * 3;
    } else if (collisionAng <= 5.375 * 2) {
        *stepX = ballSpeed * 2;
        *stepY = ballSpeed * 3;
    } else if (collisionAng <= 5.375 * 3) {
        *stepX = ballSpeed * 2;
        *stepY = ballSpeed * 2;
    } else if (collisionAng <= 5.375 * 4) {
        // This is the lower center section
        *stepX = ballSpeed * 1;
        *stepY = ballSpeed * 1;
    } else if (collisionAng <= 5.375 * 5) {
        // This is the upper center section
        *stepX = ballSpeed * 1;
        *stepY = ballSpeed * -1;
    } else if (collisionAng <= 5.375 * 6) {
        *stepX = ballSpeed * 2;
        *stepY = ballSpeed * -2;
    } else if (collisionAng <= 5.375 * 7) {
        *stepX = ballSpeed * 2;
        *stepY = ballSpeed * -3;
    } else if (collisionAng <= 5.375 * 8) {
        // This is the most upper section
        *stepX = ballSpeed * 3;
        *stepY = ballSpeed * -3;
    }

    *stepX *= dir;
}


void gameScreen() {
    //short int color = rand() % 0xFFFF;
    short int color = COLOR_WHITE;

    int score1 = 0;
    int score2 = 0;
    int balls = 10;

    int stepBallX = 0;
    int stepBallY = 0;
    int ballSpeed = 1;

    balls--;

    short int gameRunning = 1;
    short int scored = 0;

    RECTANGLE ball = {
        SCREEN_WIDTH/2 - 2,
        SCREEN_HEIGHT/2 - 2,
        5,
        5,
        color
    };

    RECTANGLE p1 = {
        10,
        100,
        5,
        40,
        color
    };

    RECTANGLE p2 = {
        305,
        100,
        5,
        40,
        color
    };

    randomBall(&ball, &stepBallX, &stepBallY, ballSpeed);

    // Update LED remaining balls
    for(int i = 0; i < balls; i++) {
        setRedLed(i, 1);
    }

    setSegDisplay2(score1);
    setSegDisplay1(score2);

    while (gameRunning) {
        if (balls <= 0 && scored) {
            gameRunning = 0;
            break;
        }

        if (scored && balls > 0) {
            int p = 0;
            for(int i = 0; i < 100000; i++) {
                p++;
                for (int j = 2; j < i; j++) {
                    if (i % j == 0) {
                        p--;
                        break;
                    }
                }
            }

            scored = 0;
            balls--;
            setRedLed(balls, 0);
            randomBall(&ball, &stepBallX, &stepBallY, ballSpeed);

            debugPrintf("\nNew ball! Remaining: %d\n", balls);
        }

        if (!getSwitchValue(1)) {
            // 2P mode
            if (getSwitchValue(0)) {
                if (p2.y > 0) p2.y -= BAR_STEP;
            } else {
                if (p2.y + p2.height < SCREEN_MAX_HEIGHT) p2.y += BAR_STEP;
            }
        } else {
            // Computer mode

            if ((p2.y + p2.height) / 2 > (ball.y + ball.height) / 2) {
                if (p2.y > 0) p2.y -= BAR_STEP;
            } else {
                if (p2.y + p2.height < SCREEN_MAX_HEIGHT) p2.y += BAR_STEP;
            }
        }

        if (getSwitchValue(17)) {
            if (p1.y > 0) p1.y -= BAR_STEP;
        } else {
            if (p1.y + p1.height < SCREEN_MAX_HEIGHT) p1.y += BAR_STEP;
        }

        short int checkScore = collisionScreenRect(ball);

        if (abs(checkScore) == 1) {
            scored = 1;

            if (checkScore == -1) {
                score2++;
                setSegDisplay1(score2);
                debugPrintf("P2 scored! Score: %d\n", score2);
            } else {
                score1++;
                setSegDisplay2(score1);
                debugPrintf("P1 scored! Score: %d\n", score1);
            }
            continue;
        }

        if (abs(collisionRect(p1, ball)) == 1) {
            debugPrintf("Collision P1 ball-puck X\n");
            fixCollisionPosition(&p1, &ball);

            changeAngle(p1, ball, &stepBallX, &stepBallY, ballSpeed);
        }
        if (abs(collisionRect(p2, ball)) == 1) {
            debugPrintf("Collision P2 ball-puck X\n");
            fixCollisionPosition(&p2, &ball);

            changeAngle(p2, ball, &stepBallX, &stepBallY, ballSpeed);
        }
        if (abs(collisionRect(p1, ball)) == 2) {
            debugPrintf("Collision P1 ball-puck Y\n");
            fixCollisionPosition(&p1, &ball);

            stepBallY *= -1;
        }
        if (abs(collisionRect(p2, ball)) == 2) {
            debugPrintf("Collision P2 ball-puck Y\n");
            fixCollisionPosition(&p1, &ball);

            stepBallY *= -1;
        }

        //debugPrintf("(%3d, %3d)x(%3d, %3d)\n", ball.x, ball.y, ball.x + ball.height, ball.y + ball.width);
        ball.x += stepBallX;
        ball.y += stepBallY;

        if ((ball.x + ball.height >= SCREEN_WIDTH - 1) || (ball.x <= 0)) {
            stepBallX *= -1;
            //debugPrintf("BOUNCE X!\n");
        }
        if ((ball.y + ball.width >= SCREEN_HEIGHT - 1) || (ball.y <= 0)) {
            stepBallY *= -1;
            //debugPrintf("BOUNCE Y!\n");
        }

        clearScreenSoft();

        drawRect(ball);
        drawRectFilled(p1);
        drawRectFilled(p2);

        updateScreen();

        waitScreen();

        clearRect(ball);
        clearRectFilled(p1);
        clearRectFilled(p2);
    }

    debugPrintf("Game over!\n");
    drawImage(img_game_over_header, 0, 0, 320, 120);

    if (score1 > score2) {
        debugPrintf("P1 won!\n");
        drawImage(img_game_over_p1, 0, 120, 320, 120);
    } else {
        debugPrintf("P2 won!\n");
        drawImage(img_game_over_p2, 0, 119, 320, 120);
    }

    updateScreen();

    while(getButtonValue(0));
    while(!getButtonValue(0));
    while(getButtonValue(0));
}

int main() {
    //srand(*((int*) 0x19438746));

    initScreen();
    clearScreenSoft();

    menuScreen();

    return 0;
}
