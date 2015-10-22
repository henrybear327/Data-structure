#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct maze {/*ALL OVER*/
    int x;
    int y;
    int flr;
};
struct maze top[10000];
struct maze tops[10000];
char maze_firstfloor[102][102], maze_secondfloor[102][102];
int temp = 1;        /*see it for return*/
int get_upstair = 0; /*stair*/
int get_downstair = 0;
int first_passby_for_mouse_one[102][102];
/*reminder*/ /*first floor for first mouse*/
int second_passby_for_mouse_one[102][102];
int first_passby_for_mouse_two[102][102];
int second_passby_for_mouse_two[102][102];
int k;
void look_first_mouse(int a, int b, int c, int d)
{
    if (top[c].flr == 1) {
        if ((maze_firstfloor[a][b] == '.' &&
             first_passby_for_mouse_one[a][b] == 0) ||
            maze_firstfloor[a][b] == 'o') { /*have best road go~go~go~*/
            switch (d) {
            case 0:
                top[c + 1].x = top[c].x + 1;
                top[c + 1].y = top[c].y;
                break;
            case 1:
                top[c + 1].x = top[c].x;
                top[c + 1].y = top[c].y + 1;
                break;
            case 2:
                top[c + 1].x = top[c].x;
                top[c + 1].y = top[c].y - 1;
                break;
            case 3:
                top[c + 1].x = top[c].x - 1;
                top[c + 1].y = top[c].y;
                break;
            }
            top[c + 1].flr = top[c].flr;
            first_passby_for_mouse_one[a][b] = 1;
            if (maze_firstfloor[a][b] == 'o')
                get_upstair = 1;
            temp = 2; /*this turn o k !!*/
        }
    } else {
        if (maze_secondfloor[a][b] == '.' &&
            second_passby_for_mouse_one[a][b] == 0) { /*have best road go~go~go~*/

            switch (d) {
            case 0:
                top[c + 1].x = top[c].x + 1;
                top[c + 1].y = top[c].y;
                break;
            case 1:
                top[c + 1].x = top[c].x;
                top[c + 1].y = top[c].y + 1;
                break;
            case 2:
                top[c + 1].x = top[c].x;
                top[c + 1].y = top[c].y - 1;
                break;
            case 3:
                top[c + 1].x = top[c].x - 1;
                top[c + 1].y = top[c].y;
                break;
            }
            top[c + 1].flr = top[c].flr;
            second_passby_for_mouse_one[a][b] = 1;
            temp = 2; /*this turn o k !!*/
        }
    }
}

void look_second_mouse(int a, int b, int c, int d)
{
    if (tops[c].flr == 2) {

        if ((maze_secondfloor[a][b] == '.' &&
             second_passby_for_mouse_two[a][b] == 0) ||
            maze_secondfloor[a][b] == 'o') { /*have best road go~go~go~*/
            switch (d) {
            case 0:
                tops[c + 1].x = tops[c].x - 1;
                tops[c + 1].y = tops[c].y;
                break;
            case 1:
                tops[c + 1].x = tops[c].x;
                tops[c + 1].y = tops[c].y - 1;
                break;
            case 2:
                tops[c + 1].x = tops[c].x;
                tops[c + 1].y = tops[c].y + 1;
                break;
            case 3:
                tops[c + 1].x = tops[c].x + 1;
                tops[c + 1].y = tops[c].y;
                break;
            }
            tops[c + 1].flr = tops[c].flr;
            second_passby_for_mouse_two[a][b] = 1;
            if (maze_secondfloor[a][b] == 'o')
                get_downstair = 1;
            temp = 2; /*this turn o k !!*/
        }
    } else {
        if (maze_firstfloor[a][b] == '.' &&
            first_passby_for_mouse_two[a][b] == 0) { /*have best road go~go~go~*/
            switch (d) {
            case 0:
                tops[c + 1].x = tops[c].x - 1;
                tops[c + 1].y = tops[c].y;
                break;
            case 1:
                tops[c + 1].x = tops[c].x;
                tops[c + 1].y = tops[c].y - 1;
                break;
            case 2:
                tops[c + 1].x = tops[c].x;
                tops[c + 1].y = tops[c].y + 1;
                break;
            case 3:
                tops[c + 1].x = tops[c].x + 1;
                tops[c + 1].y = tops[c].y;
                break;
            }
            tops[c + 1].flr = tops[c].flr;
            first_passby_for_mouse_two[a][b] = 1;
            temp = 2; /*this turn o k !!*/
        }
    }
}

int second_mouse_playing(int t)
{
    k = 0;
    look_second_mouse(tops[t].y, tops[t].x - 1, t,
                      k); /* Left > Up > Down > Right*/
    if (temp == 2) {      /*stop command*/
        temp = 1;
        t++;
        return t;
    }
    k++;
    look_second_mouse(tops[t].y - 1, tops[t].x, t, k);
    if (temp == 2) { /*stop command*/
        temp = 1;
        t++;
        return t;
    }
    k++;
    look_second_mouse(tops[t].y + 1, tops[t].x, t, k); /*down*/
    if (temp == 2) {                                   /*stop command*/
        temp = 1;
        t++;
        return t;
    }
    k++;
    look_second_mouse(tops[t].y, tops[t].x + 1, t, k); /*left*/
    if (temp == 2) {                                   /*stop command*/
        temp = 1;
        t++;
        return t;
    }
    t--;
    return t;
}
int first_mouse_playing(int i)
{
    k = 0;
    look_first_mouse(top[i].y, top[i].x + 1, i, k); /*right*/
    if (temp == 2) {                                /*stop command*/
        temp = 1;
        i++;
        return i;
    }
    k++;
    look_first_mouse(top[i].y + 1, top[i].x, i, k); /*up*/
    if (temp == 2) {                                /*stop command*/
        temp = 1;
        i++;
        return i;
    }
    k++;
    look_first_mouse(top[i].y - 1, top[i].x, i, k); /*down*/
    if (temp == 2) {                                /*stop command*/
        temp = 1;
        i++;
        return i;
    }
    k++;
    look_first_mouse(top[i].y, top[i].x - 1, i, k); /*left*/
    if (temp == 2) {                                /*stop command*/
        temp = 1;
        i++;
        return i;
    }
    i--;
    return i;
}
int search_final(int t, int i)
{
    if (top[i].x == tops[t].x && top[i].y == tops[t].y &&
        top[i].flr == tops[t].flr) { /*touch*/
        printf("they crash");
        return 3;
    } else if (top[i].x == 99 && tops[t].x == 1 && top[i].y == 99 &&
               tops[t].y == 1 && top[i].flr == 2 &&
               tops[t].flr == 1) { /*same time*/
        printf("they arrive at same time");
        return 3;
    } else if (top[i].x == 99 && top[i].y == 99 &&
               top[i].flr == 2) { /*first mouse win*/
        printf("first mouse win");
        return 3;
    } else if (tops[t].x == 1 && tops[t].y == 1 &&
               tops[t].flr == 1) { /*second mouse win*/
        printf("second mouse win");
        return 3;
    } else
        return 0;
}
int main()
{

    FILE *file;
    file = fopen("maze.txt", "r"); /*open the file*/
    if (!file) {
        printf("the file doesn't success...\n");
        exit(1);
    }
    int floor, floors, i, j, first_stair_location_right = 0,
                             first_stair_location_left = 0,
                             second_stair_location_right = 0,
                             second_stair_location_left = 0; /*declaration*/
    fscanf(file, "%d\n", &floor); /*read the floor number 1*/
    for (i = 0; i < 101; i++) {   /*read maze*/
        fscanf(file, "%s\n", maze_firstfloor[i]);
        if (first_stair_location_right != 0) /*search for stair location*/
            continue;
        for (j = 0; j < 101; j++) {
            if (maze_firstfloor[i][j] == 'o') {
                first_stair_location_right = j;
                first_stair_location_left = i;
            }
        }
    }
    fscanf(file, "%d\n", &floors); /*read the floor number 2*/
    for (i = 0; i < 101; i++) {
        fscanf(file, "%s\n", maze_secondfloor[i]);
        if (second_stair_location_right != 0) /*search for stair location*/
            continue;
        for (j = 0; j < 101; j++) {
            if (maze_secondfloor[i][j] == 'o') {
                second_stair_location_right = j;
                second_stair_location_left = i;
            }
        }
    }
    memset((void *)first_passby_for_mouse_one, 0, sizeof(int) * 102 * 102);
    memset((void *)first_passby_for_mouse_two, 0, sizeof(int) * 102 * 102);
    memset((void *)second_passby_for_mouse_one, 0, sizeof(int) * 102 * 102);
    memset((void *)second_passby_for_mouse_two, 0, sizeof(int) * 102 * 102);
    first_passby_for_mouse_one[1][1] = 1;
    second_passby_for_mouse_one[1][1] = 1;
    first_passby_for_mouse_two[1][1] = 1;
    second_passby_for_mouse_two[1][1] = 1;
    top[1].x = 1; /*cross*/
    top[1].y = 1; /*straight*/
    top[1].flr = 1;
    tops[1].x = 99;
    tops[1].y = 99;
    tops[1].flr = 2;
    i = 1; /*top*/ /*up stair?*/
    int t = 1;     /*tops*/

    int upstair_again = 0;
    int downstair_again = 0;
    int goal;
    while (1) {
        if (get_upstair == 1 && upstair_again == 0) { /**/
            upstair_again = 1;
            top[1].x = second_stair_location_right; /*cross*/
            top[1].y = second_stair_location_left;  /*straight*/
            top[1].flr = 2;
            second_passby_for_mouse_one[second_stair_location_left]
            [second_stair_location_right] = 1;
            i = 1;
            i = first_mouse_playing(i);
            printf("ratA(1,%d,%d)\n", top[i].y, top[i].x);
            t = second_mouse_playing(t);
            printf("ratB(%d,%d,%d)\n", tops[t].flr - 1, tops[t].y, tops[t].x);
            goal = search_final(t, i);
            if (goal == 3)
                break;
            continue;
        }
        if (get_downstair == 1 &&
            downstair_again == 0) { /*second & first mouse go stair together*/
            downstair_again = 1;
            tops[1].x = first_stair_location_right; /*cross*/
            tops[1].y = first_stair_location_left;  /*straight*/
            tops[1].flr = 1;
            t = 1;
            first_passby_for_mouse_two[first_stair_location_left]
            [first_stair_location_right] = 1;
            t = second_mouse_playing(t);
            i = first_mouse_playing(i);
            printf("ratA(%d,%d,%d)\n", top[i].flr - 1, top[i].y, top[i].x);
            printf("ratB(0,%d,%d)\n", tops[t].y, tops[t].x);
            goal = search_final(t, i);
            if (goal == 3)
                continue;
        }

        i = first_mouse_playing(i);
        printf("ratA(%d,%d,%d)\n", top[i].flr - 1, top[i].y, top[i].x);
        t = second_mouse_playing(t);
        printf("ratB(%d,%d,%d)\n", tops[t].flr - 1, tops[t].y, tops[t].x);

        if (tops[t].flr == 2 && tops[t].y == 11 && tops[t].x == 21)
            break;

        goal = search_final(t, i);
        if (goal == 3)
            break;
    }
    return 0;
}
