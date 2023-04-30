//
// Created by Vlad on 4/30/2023.
//

#include "snake_methods.h"
//
// Created by Vlad on 4/30/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparePoints(Point p1, Point p2){
    if(p1.x == p2.x && p1.y == p2.y)
        return 1;
    return 0;
}


Point modifyCurrentPosition(Point current_pos, char direction){
    switch (direction) {
        case 'd':
            if(current_pos.y < MAX-1)
                current_pos.y++;
            else
                // show above
                current_pos.y = 0;
            break;
        case 'a':
            if(current_pos.y > 0)
                current_pos.y--;
            else
                // show above
                current_pos.y = MAX-1;
            break;
        case 's':
            if(current_pos.x < MAX-1)
                current_pos.x++;
            else
                // show above
                current_pos.x = 0;
            break;
        case 'w':
            if(current_pos.x > 0)
                current_pos.x--;
            else
                // show above
                current_pos.x = MAX-1;
            break;
    }
    return current_pos;
}

void spawnFood(int screen[MAX][MAX]){
    //check until a free spot is found
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    srand(tm.tm_sec);
    int x, y;
    do{
        x = rand() % MAX;
        y = rand() % MAX;
        if(screen[x][y] == 0){
            screen[x][y] = 5;
        }
    }while(screen[x][y] != 5);
}

int checkIfFoodExistsAndSpawn(int screen[MAX][MAX]){
    for(int i=0; i<MAX; i++)
        for(int j=0; j<MAX; j++)
            if(screen[i][j] == 5)
                return 1;
    spawnFood(screen);
    return 0;
}

void moveSnake(Snake* snake, Point new_pos){
    for(int i=snake->length-1; i>0; i--){
        snake->body[i] = snake->body[i-1];
    }
    snake->body[0] = new_pos;
}

void eatFood(Snake* snake){
    // will add the new position at the back of the snake, opposite of the direction it is currently going
//    if(snake->length == MAX*2-1)
//        return;
    Point new_pos;
    switch (snake->direction) {
        case 'd':
            new_pos.x = snake->body[snake->length-1].x;
            new_pos.y = snake->body[snake->length-1].y-1;
            break;
        case 'a':
            new_pos.x = snake->body[snake->length-1].x;
            new_pos.y = snake->body[snake->length-1].y+1;
            break;
        case 's':
            new_pos.x = snake->body[snake->length-1].x-1;
            new_pos.y = snake->body[snake->length-1].y;
            break;
        case 'w':
            new_pos.x = snake->body[snake->length-1].x+1;
            new_pos.y = snake->body[snake->length-1].y;
            break;
    }
    snake->length++;
    snake->body = (Point*)realloc(snake->body, snake->length*sizeof(Point));
    snake->body[snake->length-1] = new_pos;
}


void restart(Snake *snake, int screen[MAX][MAX], int level){
    // reset snake
    // reset screen
    // reset food
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            screen[i][j] = 0;
    char levels[]= {"nivela.txt ", };
    Point current_pos = {MAX/2-1, MAX/2-1};

    snake->body = malloc(sizeof(Point));
    snake->body[0]=current_pos;
    snake->length=1;
    snake->direction = 's';

    // read screen from file
    levels[5] = level + '0';
    printf("Loading level %d from %s\n", level, levels);
    FILE* fp = fopen(levels, "r");
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            fscanf(fp, "%d", &screen[i][j]);
    fclose(fp);
    spawnFood(screen);
}



int reactToScreenPositionAndDrawSnake(int screen[MAX][MAX], Snake* snake){
    Point current_pos = snake->body[0];
    // change the current position to 2
    if(screen[current_pos.x][current_pos.y] == 5){
        eatFood(snake);
        eatFood(snake);
        spawnFood(screen);
    }
    if(screen[current_pos.x][current_pos.y] == 1 || screen[current_pos.x][current_pos.y] == 2){
        //game over
        printf("Game Over\n");
        return 1;
    }
    else {
        int i, overlaps = 1;
        for(i=snake->length-1; i>1; i--){
            if(comparePoints(snake->body[i], snake->body[0]))
                overlaps--;
            if(screen[snake->body[i].x][snake->body[i].y] != 2){
                screen[snake->body[i].x][snake->body[i].y] = 2;

            }
        }
        if(overlaps>=0) {
            screen[snake->body[i].x][snake->body[i].y] = 3;
        } else{
            printf("Game Over\n");
            return 1;
        }

    }
    return 0;
}

void clearScreenOfSnake(int screen[MAX][MAX], Snake* snake){
    for(int i=0; i<snake->length; i++){
        screen[snake->body[i].x][snake->body[i].y] = 0;
    }
}
Point returnScore(Snake snake, int level){
    Point score;
    score.x = (snake.length-1)/2;
    score.y = (MAX+level*2);
    return score;
}

void showDebugScreen(int screen[MAX][MAX], Snake* snake, int level){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d/%d\n", returnScore(*snake, level).x, returnScore(*snake, level).y);
}

int levelUp(int screen[MAX][MAX], Snake* snake, int level){
    if(returnScore(*snake, level).x >= (returnScore(*snake, level).y)){
        level++;
        if(level == 5){
            printf("You won!\n");
            return 1;
        }
        printf("Level %d\n", level);
        restart(snake, screen, level);
    }
    return 0;
}