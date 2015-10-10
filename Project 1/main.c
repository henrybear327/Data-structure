/*
DS Project 1
Walking mouse in a maze
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
DEBUG ARGUMENT
1 Show read_maze debug info
2
*/
#define DEBUG 2

int maze[2][110][110];

#define WALL 0
#define ROAD 1
#define STAIR 2

#define MAZE_ROW 101
#define MAZE_COL 101

void read_maze()
{
    for (int i = 0; i < 2; i++) {
        int floor;
        scanf("%d", &floor);
        floor--;

        getchar();

        for (int j = 0; j < MAZE_ROW; j++) {
            char inp[200];
            fgets(inp, 200, stdin);
            // printf("%s", inp);
            for (int k = 0; k < MAZE_COL; k++) {
                if (inp[k] == 'X')
                    maze[floor][j][k] = WALL;
                else if (inp[k] == '.')
                    maze[floor][j][k] = ROAD;
                else if (inp[k] == 'o')
                    maze[floor][j][k] = STAIR;
                // printf("%d %c %d\n", k, inp[k], maze[floor][j][k]);
            }
        }
    }

#if DEBUG <= 1
    const char conversion_to_maze[3] = {'X', '.', 'o'};
    for (int i = 0; i < 2; i++) {
        printf("%d\n", i + 1);
        for (int j = 0; j < MAZE_ROW; j++) {
            for (int k = 0; k < MAZE_COL; k++) {
                printf("%c", conversion_to_maze[maze[i][j][k]]);
            }
            printf("\n");
        }
    }
#endif
}

typedef struct state {
    int f, x, y;
    int next_dir;
} State;

const int dirA[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
const int dirB[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

State stackA[MAZE_ROW * MAZE_COL * 2 + 10];
State stackB[MAZE_ROW * MAZE_COL * 2 + 10];
int posA = 0, posB = 0;

bool is_same_location(State A, State B)
{
    return A.x == B.x && A.y == B.y && A.f == B.f;
}

bool is_A_dest(State A)
{
    return A.f == 1 && A.x == 99 && A.y == 99;
}

bool is_B_dest(State B)
{
    return B.f == 0 && B.x == 1 && B.y == 1;
}

int main()
{
    read_maze(); // get input from file

    // init
    State ratA = {0, 1, 1, 0};
    State ratB = {1, 99, 99, 0};

    stackA[posA++] = ratA;
    stackB[posB++] = ratB;

    // if one of them reached the dest. or they meet, terminate
    while (!is_A_dest(ratA) && !is_B_dest(ratB) &&
           !is_same_location(ratA, ratB) == false) {
    }

    return 0;
}
