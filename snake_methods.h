//
// Created by Vlad on 4/30/2023.
//

#ifndef TEST_USE_LIBRARY_IN_C_SNAKE_METHODS_H
#define TEST_USE_LIBRARY_IN_C_SNAKE_METHODS_H

#define MAX 10
enum Direction {UP='w', DOWN='s', LEFT='a', RIGHT='d'};

typedef struct {
    int x, y;
}Point;

typedef struct {
    Point* body;
    int length;
    char direction;
}Snake;
void readLevel(int screen[MAX][MAX], char level[]);
void spawnFood(int screen[MAX][MAX]);
void moveSnake(Snake* snake, Point new_pos);
void eatFood(Snake* snake);
void restart(Snake* snake, int screen[MAX][MAX], int level);
int levelUp(int screen[MAX][MAX], Snake* snake, int level);
int checkIfFoodExistsAndSpawn(int screen[MAX][MAX]);
Point modifyCurrentPosition(Point current_pos, char direction);
int comparePoints(Point p1, Point p2);
int reactToScreenPositionAndDrawSnake(int screen[MAX][MAX], Snake* snake);
void clearScreenOfSnake(int screen[MAX][MAX], Snake* snake);
void showDebugScreen(int screen[MAX][MAX], Snake* snake, int level);
Point returnScore(Snake snake, int level);
#endif //TEST_USE_LIBRARY_IN_C_SNAKE_METHODS_H
