#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
            for (int k = 0; k < MAZE_COL; k++) {
                if (inp[k] == 'X')
                    maze[floor][j][k] = WALL;
                else if (inp[k] == '.')
                    maze[floor][j][k] = ROAD;
                else if (inp[k] == 'o')
                    maze[floor][j][k] = STAIR;
            }
        }
    }
}

typedef struct state {
    int f, x, y;
} State;

// rat A and rat B's moving direction, default order
const int dirA[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
const int dirB[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

// stack for rat A and rat B
State stackA[MAZE_ROW * MAZE_COL * 2 + 10];
State stackB[MAZE_ROW * MAZE_COL * 2 + 10];
int posA = 0, posB = 0;

// map for marking visited or not
bool visitedA[2][MAZE_ROW][MAZE_COL], visitedB[2][MAZE_ROW][MAZE_COL];

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

bool is_bounded(int x, int y)
{
    return 0 <= x && x < MAZE_ROW && 0 <= y && y < MAZE_COL;
}

int main()
{
    // use freopen if you wish!
    // freopen("maze.txt", "r", stdin);
    // freopen("result.txt", "w", stdout);

    // get input from file
    read_maze();

    // print out the maze
    const char conversion_to_maze[3] = {'X', '.', 'o'};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < MAZE_ROW; j++) {
            for (int k = 0; k < MAZE_COL; k++) {
                printf("%c", conversion_to_maze[maze[i][j][k]]);
            }
            printf("\n");
        }
    }

    // initialize the stacks and map
    State ratA = {0, 1, 1};
    State ratB = {1, 99, 99};

    posA = posB = 0;
    stackA[posA++] = ratA;
    stackB[posB++] = ratB;
    visitedA[0][1][1] = visitedB[1][99][99] = true;

    // if one of them reached the dest. or they meet, terminate
    while (1) {
        State curr;

        // walk mouse A

        // check stackA status
        if (posA == 0) {
            printf("Empty stack A! Something is wrong!\n");
            return 0;
        }

        curr = stackA[posA - 1]; // get the top element from stack
        bool has_next_step = false;

        for (int i = 0; i < 4; i++) {
            // calculate the next location to go to
            int tmpf = curr.f;
            int tmpx = curr.x + dirA[i][0];
            int tmpy = curr.y + dirA[i][1];
            if (is_bounded(tmpx, tmpy) && maze[tmpf][tmpx][tmpy] != WALL &&
                visitedA[tmpf][tmpx][tmpy] == false) {
                // if the calculated new location is not out-of-maze, not the wall, and
                // not visited
                visitedA[tmpf][tmpx][tmpy] =
                    true; // go to that location and mark it as visited

                // check if this location is a stair and if this mouse is allow to go
                // through that stair
                if (maze[tmpf][tmpx][tmpy] == STAIR && tmpf == 0) {
                    State next_step = {1, tmpx, tmpy}; // push the location AFTER going
                    // through the stair into the stack
                    stackA[posA++] = next_step;
                    visitedA[1][tmpx][tmpy] = true; // mark the location after going
                    // through the stair as visited
                    has_next_step = true;
                } else {
                    State next_step = {tmpf, tmpx, tmpy};
                    stackA[posA++] = next_step; // push the visited location into the
                    // stack
                    has_next_step = true;
                }
                break;
            }
        }

        if (has_next_step == false)
            /*
            has_next_step means if the mouse can not move to the next location, then
            go back to the previous location.
            */
            posA--;

        // walk mouse B(the code is just copy paste from the walk mouse A, so check
        // the comments above)

        // check stackB status
        if (posB == 0) {
            printf("Empty stack B! Something is wrong!\n");
            return 0;
        }

        curr = stackB[posB - 1];
        has_next_step = false;

        for (int i = 0; i < 4; i++) {
            int tmpf = curr.f;
            int tmpx = curr.x + dirB[i][0];
            int tmpy = curr.y + dirB[i][1];
            if (is_bounded(tmpx, tmpy) && maze[tmpf][tmpx][tmpy] != WALL &&
                visitedB[tmpf][tmpx][tmpy] == false) {
                visitedB[tmpf][tmpx][tmpy] = true;
                // check stair and mouse hasn't move up/down at any stairs yet
                if (maze[tmpf][tmpx][tmpy] == STAIR && curr.f == 1) {
                    State next_step = {0, tmpx, tmpy};
                    visitedB[0][tmpx][tmpy] = true;
                    stackB[posB++] = next_step;
                    has_next_step = true;
                } else {
                    State next_step = {tmpf, tmpx, tmpy};
                    stackB[posB++] = next_step;
                    has_next_step = true;
                }
                break;
            }
        }

        if (has_next_step == false)
            posB--;

        // print result
        if (is_same_location(stackA[posA - 1], stackB[posB - 1])) {
            // if at same location, print A location and the message
            printf("ratA(%d,%d,%d)\n", stackA[posA - 1].f, stackA[posA - 1].x,
                   stackA[posA - 1].y);
            printf("rats encounter each other in (%d,%d,%d)\n", stackA[posA - 1].f,
                   stackA[posA - 1].x, stackA[posA - 1].y);
            break;
        } else if (is_B_dest(stackB[posB - 1])) {
            // if reaches B, print A's location and the message
            printf("ratA(%d,%d,%d)\n", stackA[posA - 1].f, stackA[posA - 1].x,
                   stackA[posA - 1].y);
            printf("rats didn't encounter each other in this maze\n");
            break;
        } else if (is_A_dest(stackA[posA - 1])) {
            // if reaches A, then just print the message
            printf("rats didn't encounter each other in this maze\n");
            break;
        } else {
            // just print both A and B's location
            printf("ratA(%d,%d,%d)\n", stackA[posA - 1].f, stackA[posA - 1].x,
                   stackA[posA - 1].y);
            printf("ratB(%d,%d,%d)\n", stackB[posB - 1].f, stackB[posB - 1].x,
                   stackB[posB - 1].y);
        }
    }

    return 0;
}
