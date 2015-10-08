/*
DS Project 1
Walking mouse in a maze
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 1

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
		//printf("%d %c %d\n", k, inp[k], maze[floor][j][k]);
            }
        }
    }

#if DEBUG
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

int main()
{
    read_maze();
    
    

    return 0;
}
