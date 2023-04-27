#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

typedef struct {
    int x, y;
}Point;

typedef struct {
    Point* body;
    int length;
    char direction;
}Snake;

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

int Draw(int screen[MAX][MAX], Snake* snake, int level){
    // delete console
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

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

        for(int i=0; i<snake->length; i++)
            screen[snake->body[i].x][snake->body[i].y] = 2;
        //screen[current_pos.x][current_pos.y] = 2;
    }

    // show screen
    int isFood = 0;
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            printf("%d ", screen[i][j]);
            if(screen[i][j] == 5)
                isFood = 1;
        }
        printf("\n");
    }
    printf("Score: %d/%d\n", (snake->length-1)/2, (MAX+level*2));
    if(!isFood)
        spawnFood(screen);

    for(int i=0; i<snake->length; i++)
        screen[snake->body[i].x][snake->body[i].y] = 0;

    snake->direction = getchar();

    switch (snake->direction) {
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
        case 'q':
            return 1;
            break;
    }
    moveSnake(snake, current_pos);
    return 0;
}

void restart(Snake *snake, int screen[MAX][MAX], int level){
    // reset snake
    // reset screen
    // reset food
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


int main() {
    int level = 0;
    int screen[MAX][MAX];
    Snake snake;
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            screen[i][j] = 0;
    restart(&snake, screen, level);
    while(1){
        if(snake.length >= (MAX+level*2)*2){
            level++;
            if(level == 5){
                printf("You won!\n");
                break;
            }
            printf("Level %d\n", level);
            restart(&snake, screen, level);
        }
        if(Draw(screen, &snake, level))
            break;
    }

    return 0;
}
