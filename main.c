#include <stdio.h>
#include "snake_methods.h"

int Draw(int screen[MAX][MAX], Snake* snake, int level){
    // delete console
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    Point current_pos = snake->body[0];
    // change the current position to 2
    if(reactToScreenPositionAndDrawSnake(screen, snake))
        return 1;
    checkIfFoodExistsAndSpawn(screen);
    showDebugScreen(screen, snake, level);
    // clear screen if snake
    clearScreenOfSnake(screen, snake);

    snake->direction = getchar();

    switch (snake->direction) {
        case 'q':
            return 1;
        default: current_pos = modifyCurrentPosition(current_pos, snake->direction);
            break;
    }
    moveSnake(snake, current_pos);
    return 0;
}


int main() {
   int level = 0;
    int screen[MAX][MAX];
    Snake snake;

    restart(&snake, screen, level);
    while(1){
        if(levelUp(screen, &snake, level)){
            break;
        }
        if(Draw(screen, &snake, level))
            break;
    }

    return 0;
}
