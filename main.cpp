#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "drawlib/screen.c"
#include "drawlib/draw.c"
#include "drawlib/physics.c"

#include "controllerlib/controller.c"

#define BAR_STEP 2

void startScreen();
void creditsScreen();
void gameScreen();
int main();

void startScreen() {
    // TODO:
    // - Print the game main menu screen
    //    - Start game
    //    - Credits
    //    - Easter egg???

    // Skip to the game until we have no menu yet...
    gameScreen();
}

void creditsScreen() {
    // TODO
}


void randomBall(RECTANGLE *ball, float *stepX, float *stepY, float ballSpeed) {
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

void changeAngle(RECTANGLE p, RECTANGLE b, float *stepX, float *stepY, float ballSpeed) {
    float collisionAng = (p.y - b.y + p.height - 1);

    short int dir = *stepX > 0 ? -1 : 1;

    printf("Angle: %f, Dir: %d\n", collisionAng, dir);

    if (collisionAng <= 5.375 * 1) {
        // This is the most lower section
        *stepX = ballSpeed * 3;
        *stepY = ballSpeed * 3;
    } else if (collisionAng <= 5.375 * 2) {
        *stepX = ballSpeed * 2;
        *stepY = ballSpeed * 2;
    } else if (collisionAng <= 5.375 * 3) {
        *stepX = ballSpeed * 1.5;
        *stepY = ballSpeed * 1.5;
    } else if (collisionAng <= 5.375 * 4) {
        // This is the lower center section
        *stepX = ballSpeed * 1;
        *stepY = ballSpeed * 0.5;
    } else if (collisionAng <= 5.375 * 5) {
        // This is the upper center section
        *stepX = ballSpeed * 1;
        *stepY = ballSpeed * -0.5;
    } else if (collisionAng <= 5.375 * 6) {
        *stepX = ballSpeed * 1.5;
        *stepY = ballSpeed * -1.5;
    } else if (collisionAng <= 5.375 * 7) {
        *stepX = ballSpeed * 2;
        *stepY = ballSpeed * -2;
    } else if (collisionAng <= 5.375 * 8) {
        // This is the most upper section
        *stepX = ballSpeed * 3;
        *stepY = ballSpeed * -3;
    }

    *stepX *= dir;
}


void gameScreen() {
    short int color = rand() % 0xFFFF;
    short int btnLock = 0;

    int score1 = 0;
    int score2 = 0;
    int balls = 10;

    float stepBallX = 0;
    float stepBallY = 0;
    float ballSpeed = 1;

    balls--;

    short int gameRunning = 1;
    short int scored = 0;

    int cmReturn;

    RECTANGLE ball = {
        .x = SCREEN_WIDTH/2 - 2,
        .y = SCREEN_HEIGHT/2 - 2,
        .width = 5,
        .height = 5,
        .color = color
    };

    RECTANGLE p1 = {
        .x = 10,
        .y = 100,
        .width = 5,
        .height = 40,
        .color = color
    };

    RECTANGLE p2 = {
        .x = 305,
        .y = 100,
        .width = 5,
        .height = 40,
        .color = color
    };

    randomBall(&ball, &stepBallX, &stepBallY, ballSpeed);

    // Update LED remaining balls
    for(int i = 0; i < balls; i++) {
        setRedLed(i, 1);
    }

    while (gameRunning) {
        do {
            cmReturn = controllerMaintain();
        } while(cmReturn == 1);

        if (cmReturn == 2) {
            gameRunning = 0;
            break;
        }

        if (balls == 0 && scored) {
            gameRunning = 0;
            break;
        }

        if (getButtonValue(0) && !btnLock) {
            printf("\nNew ball\n");
            scored = 0;
            btnLock = 1;
            balls--;
            setRedLed(balls, 0);
            randomBall(&ball, &stepBallX, &stepBallY, ballSpeed);
        }
        if (getButtonValue(0)) continue;
        btnLock = 0;

        if (scored) continue;

        if (getSwitchValue(0)) {
            if (p2.y > 0) p2.y -= BAR_STEP;
        } else {
            if (p2.y + p2.height < SCREEN_MAX_HEIGHT) p2.y += BAR_STEP;
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
                setSegDisplay2(score2);
                printf("P2 scored! Score: %d\n", score2);
            } else {
                score1++;
                setSegDisplay1(score1);
                printf("P1 scored! Score: %d\n", score1);
            }
            continue;
        }

        if (abs(collisionRect(p1, ball)) == 1) {
            printf("Collision P1 ball-puck X\n");
            fixCollisionPosition(&p1, &ball);

            changeAngle(p1, ball, &stepBallX, &stepBallY, ballSpeed);
        }
        if (abs(collisionRect(p2, ball)) == 1) {
            printf("Collision P2 ball-puck X\n");
            fixCollisionPosition(&p2, &ball);

            changeAngle(p2, ball, &stepBallX, &stepBallY, ballSpeed);
        }
        if (abs(collisionRect(p1, ball)) == 2) {
            printf("Collision P1 ball-puck Y\n");
            fixCollisionPosition(&p1, &ball);

            stepBallY *= -1;
        }
        if (abs(collisionRect(p2, ball)) == 2) {
            printf("Collision P2 ball-puck Y\n");
            fixCollisionPosition(&p1, &ball);

            stepBallY *= -1;
        }

        //printf("(%3d, %3d)x(%3d, %3d)\n", ball.x, ball.y, ball.x + ball.height, ball.y + ball.width);
        ball.x += stepBallX;
        ball.y += stepBallY;

        if ((ball.x + ball.height >= SCREEN_WIDTH - 1) || (ball.x <= 0)) {
            stepBallX *= -1;
            //printf("BOUNCE X!\n");
        }
        if ((ball.y + ball.width >= SCREEN_HEIGHT - 1) || (ball.y <= 0)) {
            stepBallY *= -1;
            //printf("BOUNCE Y!\n");
        }

        clearScreen();

        drawRect(ball);
        drawRectFilled(p1);
        drawRectFilled(p2);

        updateScreen();

        waitScreen();

        clearRect(ball);
        clearRectFilled(p1);
        clearRectFilled(p2);
    }

    printf("Game over!\n");

    if (score1 > score2) {
        printf("P1 won!\n");
    } else {
        printf("P2 won!\n");
    }


}

int main() {
    srand((unsigned int) time(NULL));

    initScreen();

    startScreen();

    return 0;
}
