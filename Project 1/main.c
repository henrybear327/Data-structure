/*
DS Project 1
Walking mouse in a maze
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

bool is_bounded(State A)
{
    return 0 <= A.x && A.x < MAZE_ROW && 0 <= A.y && A.y < MAZE_COL;
}

int main()
{
    read_maze(); // get input from file

    // init
    State ratA = {0, 1, 1, 0};
    State ratB = {1, 99, 99, 0};

    posA = posB = 0;
    stackA[posA++] = ratA;
    stackB[posB++] = ratB;

    bool visitedA[2][MAZE_ROW][MAZE_COL], visitedB[2][MAZE_ROW][MAZE_COL];
    memset(visitedA, 0, sizeof(visitedA));
    memset(visitedB, 0, sizeof(visitedB));

    // if one of them reached the dest. or they meet, terminate
    while (!is_A_dest(stackA[posA - 1]) && !is_B_dest(stackB[posB - 1]) &&
           is_same_location(stackA[posA - 1], stackB[posB - 1]) == false) {
        // write down all of the var and struct first
        // plan the manually crafted DFS flow

        State curr;
        // walk mouse A

        // printf("Walk Mouse A\n");
        while (posA != 0) {
            curr = stackA[posA - 1];
            visitedA[curr.f][curr.x][curr.y] = true;
            // printf("curr -> %d %d %d %d\n", curr.f, curr.x, curr.y, curr.next_dir);

            bool has_next_step = false;
            if (maze[curr.f][curr.x][curr.y] == STAIR && curr.f == 0) {
                // RatA can only go up once!
                curr.f = 1;
                stackA[posA++] = curr;
                has_next_step = true;
            } else {
                for (int i = curr.next_dir; i < 4; i++) {
                    // printf("Trying %d dirA\n", i);
                    State tmp = curr;
                    tmp.x = curr.x + dirA[i][0];
                    tmp.y = curr.y + dirA[i][1];
                    tmp.next_dir = 0;
                    // printf("tmp -> %d %d %d %d\n", tmp.f, tmp.x, tmp.y, tmp.next_dir);
                    if (is_bounded(tmp) && maze[tmp.f][tmp.x][tmp.y] != WALL &&
                        visitedA[tmp.f][tmp.x][tmp.y] == false) {
                        // printf("posA %d\n", posA);

                        stackA[posA - 1].next_dir = i + 1;
                        stackA[posA++] = tmp;
                        has_next_step = true;
                        break;
                    }
                }
            }

            if (has_next_step == false) {
                posA--;
                printf("ratA(%d,%d,%d)\n", stackA[posA - 1].f, stackA[posA - 1].x,
                       stackA[posA - 1].y);
                break;
            } else {
                printf("ratA(%d,%d,%d)\n", stackA[posA - 1].f, stackA[posA - 1].x,
                       stackA[posA - 1].y);
                break;
            }
        }

        // walk mouse B (walk one mouse first)

        // printf("Walk Mouse B\n");
        while (posB != 0) {
            curr = stackB[posB - 1];
            visitedB[curr.f][curr.x][curr.y] = true;
            // printf("curr -> %d %d %d %d\n", curr.f, curr.x, curr.y, curr.next_dir);

            bool has_next_step = false;
            if (maze[curr.f][curr.x][curr.y] == STAIR && curr.f == 1) {
                // RatB can only go down once!
                curr.f = 0;
                stackB[posB++] = curr;
                has_next_step = true;
            } else {
                for (int i = curr.next_dir; i < 4; i++) {
                    // printf("Trying %d dirB\n", i);
                    State tmp = curr;
                    tmp.x = curr.x + dirB[i][0];
                    tmp.y = curr.y + dirB[i][1];
                    tmp.next_dir = 0;
                    // printf("tmp -> %d %d %d %d\n", tmp.f, tmp.x, tmp.y, tmp.next_dir);
                    if (is_bounded(tmp) && maze[tmp.f][tmp.x][tmp.y] != WALL &&
                        visitedB[tmp.f][tmp.x][tmp.y] == false) {
                        // printf("posB %d\n", posB);

                        stackB[posB - 1].next_dir = i + 1;
                        stackB[posB++] = tmp;
                        has_next_step = true;
                        break;
                    }
                }
            }

            if (has_next_step == false) {
                posB--;
                printf("ratB(%d,%d,%d)\n", stackB[posB - 1].f, stackB[posB - 1].x,
                       stackB[posB - 1].y);
                break;
            } else {
                printf("ratB(%d,%d,%d)\n", stackB[posB - 1].f, stackB[posB - 1].x,
                       stackB[posB - 1].y);
                break;
            }
        }
    }

    return 0;
}
