#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "drawlib/screen.c"
#include "drawlib/draw.c"
#include "drawlib/physics.c"

#include "controllerlib/controller.c"

#define BAR_STEP 5

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

void gameScreen() {
    float stepBallX = 0.7071;
    float stepBallY = 0.7071;
    short int color = rand() % 0xFFFF;

    short int gameRunning = 1;

    short int scored = 0;

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

    while (gameRunning) {
        sf::Event event;

        while (screen_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                screen_window.close();
                gameRunning = 0;
            }

            if (event.type == sf::Event::KeyPressed) {
                //printf("Key: %d\n", event.key.code);

                switch(event.key.code) {
                case 22: // W key
                    if (p1.y <= 0) break;
                    p1.y += -BAR_STEP;
                    //printf("P1 Up: %d %d\n", p1.y1, p1.y2);
                    break;
                case 18: // S key
                    if (p1.y + p1.height >= SCREEN_HEIGHT - 1) break;
                    p1.y += BAR_STEP;
                    //printf("P1 Down: %d %d\n", p1.y1, p1.y2);
                    break;
                case 73: // Up arrow
                    if (p2.y <= 0) break;
                    p2.y += -BAR_STEP;
                    //printf("P2 Up: %d %d\n", p2.y1, p2.y2);
                    break;
                case 74: // Down arrow
                    if (p2.y + p2.height >= SCREEN_HEIGHT-1) break;
                    p2.y += BAR_STEP;
                    //printf("P2 Down: %d %d\n", p2.y1, p2.y2);
                    break;
                case 58: // Enter key
                    scored = 0;
                    ball.x = SCREEN_WIDTH/2 - 2;
                    ball.y = SCREEN_HEIGHT/2 - 2;
                    stepBallX = rand() % 3 - 2;
                    stepBallY = rand() % 3 - 2;
                default:
                    break;
                }
            }
        }

        if (scored) continue;

        if (abs(collisionScreenRect(ball)) == 1) {
            scored = 1;
            continue;
        }

        if (abs(collisionRect(p1, ball)) == 1 || abs(collisionRect(p2, ball)) == 1) {
            stepBallX *= -1;
        }
        if (abs(collisionRect(p1, ball)) == 2 || abs(collisionRect(p2, ball))) {
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
}

int main() {
    srand((unsigned int) time(NULL));

    initScreen();

    startScreen();

    return 0;
}
