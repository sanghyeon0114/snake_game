#include "console.h"

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

int x = BOARD_SIZE/2;
int y = BOARD_SIZE/2;
int score = 0;

enum Direction { D_RIGHT = 0, D_LEFT = 1, D_UP = 2, D_DOWN = 3 };
int direction = D_RIGHT;

int snakeBody[((BOARD_SIZE-2) * (BOARD_SIZE-2))-1][2];
int snakeBodyLength = 0;

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
    if (console::key(console::K_LEFT)) {
        direction = D_LEFT;
    }
    if (console::key(console::K_RIGHT)) {
        direction = D_RIGHT;
    }
    if (console::key(console::K_UP)) {
        direction = D_UP;
    }
    if (console::key(console::K_DOWN)) {
        direction = D_DOWN;
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

bool isEndGame() {
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

void loseMessage() {
    string message1 = "YOU LOSE!";
    string message2 = "Try again? (Enter)";
    console::draw(BOARD_SIZE/2 - message1.length()/2, BOARD_SIZE/2, message1);
    console::draw(BOARD_SIZE/2 - message2.length()/2, BOARD_SIZE/2+1, message2);
}

void game() {
    // int map[BOARD_SIZE][BOARD_SIZE];

    // for(int i = 0; i < BOARD_SIZE; i++) {
    //     for(int j = 0; j < BOARD_SIZE; j++) {
    //         if(i == 0 || j == 0 || i == BOARD_SIZE-1 || j == BOARD_SIZE-1) {
    //             map[i][j] = 1;
    //         } else {
    //             map[i][j] = 0;
    //         }
    //     }
    // }

    initGame();
    console::init();

    int frame = 0;

    while (true) {
        console::clear();

        drawMap();
        drawScore();

        handleInput();
        restrictInScreen();
        drawSnake();

        if(frame % MOVE_DELAY == 0) {
            moveSnake();
            frame = 0;
        }
        if(isEndGame()) {
            loseMessage();
            break;
        }
        
        frame++;
        console::wait();
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
        } else if(console::key(console::K_ESC)) {
            break;
        }

        console::wait();
    }

    return 0;
}