#include "console.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

#define BOARD_SIZE 20
#define MOVE_DELAY 15
#define WALL_VERTICAL_STRING "┃"
#define WALL_HORIZONTAL_STRING "━"
#define WALL_RIGHT_TOP_STRING "┓"
#define WALL_LEFT_TOP_STRING "┏"
#define WALL_RIGHT_BOTTOM_STRING "┛"
#define WALL_LEFT_BOTTOM_STRING "┗"
#define SNAKE_STRING "■"
#define SNAKE_BODY_STRING "■"
#define APPLE_STRING "●"

bool isStop = false;

int x = BOARD_SIZE/2;
int y = BOARD_SIZE/2;
int score = 0;

enum Direction { D_RIGHT = 0, D_LEFT = 1, D_UP = 2, D_DOWN = 3 };
int direction = D_RIGHT;

int snakeBody[((BOARD_SIZE-2) * (BOARD_SIZE-2))-1][2];
int snakeBodyLength = 0;

int applePosition[2] = {-1, -1};

bool validSnakePath(int snakeX, int snakeY) {
    return !(snakeBodyLength > 0 && snakeX == snakeBody[0][0] && snakeY == snakeBody[0][1]);
}

void moveSnake() {
    if(direction == D_RIGHT) {
        x++;
    } else if(direction == D_LEFT) {
        x--;
    } else if(direction == D_UP) {
        y--;
    } else if(direction == D_DOWN) {
        y++;
    }
}

void handleInput() {
    if (console::key(console::K_LEFT) && validSnakePath(x-1, y)) {
        direction = D_LEFT;
    }
    if (console::key(console::K_RIGHT) && validSnakePath(x+1, y)) {
        direction = D_RIGHT;
    }
    if (console::key(console::K_UP) && validSnakePath(x, y-1)) {
        direction = D_UP;
    }
    if (console::key(console::K_DOWN) && validSnakePath(x, y+1)) {
        direction = D_DOWN;
    }
    if (console::key(console::K_ESC)) {
        isStop = true;
    }
}

void restrictInScreen() {
    if (x < 0)
        x = 0;
    if (x >= console::SCREEN_WIDTH)
        x = console::SCREEN_WIDTH - 1;
    if (y < 0)
        y = 0;
    if (y >= console::SCREEN_HEIGHT)
        y = console::SCREEN_HEIGHT - 1;
}

void drawSnake() {
    console::draw(x, y, SNAKE_STRING);
}

void drawMap() {
    console::draw(0, 0, WALL_LEFT_TOP_STRING);
    console::draw(0, BOARD_SIZE-1, WALL_LEFT_BOTTOM_STRING);
    console::draw(BOARD_SIZE-1, 0, WALL_RIGHT_TOP_STRING);
    console::draw(BOARD_SIZE-1, BOARD_SIZE-1, WALL_RIGHT_BOTTOM_STRING);

    for(int i = 1; i < BOARD_SIZE-1; i++) {
        console::draw(0, i, WALL_VERTICAL_STRING);
        console::draw(i, 0, WALL_HORIZONTAL_STRING);
        console::draw(BOARD_SIZE-1, i, WALL_VERTICAL_STRING);
        console::draw(i, BOARD_SIZE-1, WALL_HORIZONTAL_STRING);
    }
}

void drawScore() {
    string viewScore = "Score: ";
    viewScore.append(1, (char)(score + 48));
    console::draw(BOARD_SIZE/2 - viewScore.length()/2, BOARD_SIZE, viewScore);
}

void randomApple() {
    srand(time(NULL));
    applePosition[0] = rand() % (BOARD_SIZE-2) + 1;
    applePosition[1] = rand() % (BOARD_SIZE-2) + 1;
}

void drawApple() {
    console::draw(applePosition[0], applePosition[1], APPLE_STRING);
}

void getApple() {
    if(x == applePosition[0] && y == applePosition[1]) {
        snakeBodyLength++;
        randomApple();
    }
}

void moveSnakeBody() {
    for(int i = snakeBodyLength-1; i > 0; i--) {
        snakeBody[i][0] = snakeBody[i-1][0];
        snakeBody[i][1] = snakeBody[i-1][1];
    }
    snakeBody[0][0] = x;
    snakeBody[0][1] = y;
}

void drawSnakeBody() {
    for(int i = 0; i < snakeBodyLength; i++) {
        console::draw(snakeBody[i][0], snakeBody[i][1], SNAKE_BODY_STRING);
    }
}

void initGame() {
    x = BOARD_SIZE/2;
    y = BOARD_SIZE/2;
    score = 0;

    direction = D_RIGHT;

    for(int i = 0; i < ((BOARD_SIZE-2) * (BOARD_SIZE-2))-1; i++) {
        snakeBody[i][0] = 0;
        snakeBody[i][1] = 0;
    }
    snakeBodyLength = 0;
}

bool isLoseGame() {
    if(x <= 0 || y <= 0 || x >= BOARD_SIZE-1 || y >= BOARD_SIZE-1) {
        return true;
    }
    if(snakeBodyLength > 0) {
        for(int i = 0; i < snakeBodyLength; i++) {
            if(snakeBody[i][0] == x && snakeBody[i][1] == y) {
                return true;
            }
        }
    }
    return false;
}

bool isESC() {
    return isStop;
}

void loseMessage() {
    string message1 = "YOU LOSE!";
    string message2 = "Try again? (Enter)";
    console::draw(BOARD_SIZE/2 - message1.length()/2, BOARD_SIZE/2, message1);
    console::draw(BOARD_SIZE/2 - message2.length()/2, BOARD_SIZE/2+1, message2);
}

void game() {
    initGame();
    console::init();

    randomApple();

    int frame = 0;

    while (true) {
        console::clear();

        drawMap();
        drawScore();
        drawApple();
        handleInput();
        restrictInScreen();

        if(frame % MOVE_DELAY == 0) {
            moveSnakeBody();
            moveSnake();
            getApple();
            frame = 0;
        }

        drawSnakeBody();
        drawSnake();

        frame++;
        console::wait();

        if(isLoseGame()) {
            loseMessage();
            break;
        } else if(isESC()) {
            break;
        }
    }
}

int main() {
    bool isStart = true;
    while(true) {
        
        if(isStart) {
            game();
            isStart = false;
        }

        if(console::key(console::K_ENTER)) {
            isStart = true;
        } else if(isStop || console::key(console::K_ESC)) {
            break;
        }

        console::wait();
    }

    return 0;
}