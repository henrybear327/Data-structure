#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_COL 101
#define MAX_ROW 101

int map[2][MAX_ROW][MAX_COL];
// save the map


void read()
{
    for(int i=0; i<2; i++)
    {
        int howfloor;
        scanf("%d",&howfloor);
        howfloor--;
        getchar();
        for (int j = 0; j < MAX_ROW; j++)
        {
            char inp[200];
            fgets(inp, 200, stdin);
            for (int k = 0; k < MAX_COL; k++)
            {
                if (inp[k] == 'X')
                    map[howfloor][j][k] = 0;
                else if (inp[k] == '.')
                    map[howfloor][j][k] = 1;
                else if (inp[k] == 'o')
                    map[howfloor][j][k] = 2;
            }
        }
    }
}
//read in the map & set the wall=0 the road=1 the stair=2
typedef struct
{
    int vert;
    int horiz;
} offset;

offset amove[4]= {{0,1},{1,0},{-1,0},{0,-1}};
offset bmove[4]= {{0,-1},{-1,0},{1,0},{0,1}};

//set the array of two rats'  path  order
typedef struct
{
    int floor;
    int row;
    int col;
} element;

//set floor,row,col struct for reconding rata or ratb
element stackA[200000];
element stackB[200000];
int atop=0,btop=0;

bool amark[2][MAX_ROW][MAX_COL];
bool bmark[2][MAX_ROW][MAX_COL];

//it is to mark yes or no pass by

bool is_same_location(element A, element B)
{
    return A.row == B.row && A.col == B.col && A.floor == B.floor;
}
// they are meet

bool is_A_dest(element A)
{
    return A.floor == 1 && A.row == 99 && A.col == 99;
}
//rata walk to ratb begin

bool is_B_dest(element B)
{
    return B.floor == 0 && B.row == 1 && B.col == 1;
}

//ratb walk to rata begin

bool is_bounded(int x, int y)
{
    return 0 <= x && x < MAX_ROW && 0 <= y && y < MAX_COL;
}


int main()
{
    freopen("3_maze.txt","r",stdin);
    freopen("result.txt","w",stdout);
    read();
    const char conversion_to_maze[3] = {'X', '.', 'o'};
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            for (int k = 0; k < MAX_COL; k++)
            {
                printf("%c", conversion_to_maze[map[i][j][k]]);
            }
            printf("\n");
        }
    }
    //output the map
    element ratA= {0,1,1};
    element ratB= {1,99,99};

    // initialize the coordinates
    atop = btop = 0;
    stackA[atop++] = ratA;
    stackB[btop++] = ratB;

    // set the stack

    amark[0][1][1]=true;
    bmark[1][99][99]=true;

    // begin coordinates must set pass by

    while(1)
    {
        element position;

        if(atop==0)
        {
            printf("empty stack a");
            return 0;
        }
        position=stackA[atop-1];
        bool has_next_step=false;
        for(int i=0; i<4; i++)
        {
            // rata begin walk by path order
            int tempf=position.floor;
            int tempx=position.row+amove[i].vert;
            int tempy=position.col+amove[i].horiz;
            if( is_bounded(tempx,tempy)&&map[tempf][tempx][tempy]!=0&&amark[tempf][tempx][tempy]==false)
            {
                amark[tempf][tempx][tempy]=true;

                //the rata pass by the path should be recond
                if(map[tempf][tempx][tempy]==2&&tempf==0)
                {

                    //it is  differentiate stair. If it is a stair ,the rat must into the stair.
                    //save the x,y coordinates enter the stack a and mark the path
                    element next_step = {1,tempx,tempy};
                    stackA[atop++]=next_step;
                    amark[1][tempx][tempy]=true;
                    has_next_step=true;
                }
                else
                {
                    //If it is no a stair,direcrly the x,y coordinates enter the satack and mark the path
                    element next_step= {tempf,tempx,tempy};
                    stackA[atop++]=next_step;
                    has_next_step=true;
                }
                break;
            }
        }
        // if rata the path meet the wall,step by step will stack atop--
        if(has_next_step==false)
            atop--;


        if(btop==0)
        {
            printf("empty stack b");
            return 0;
        }
        position=stackB[btop-1];
        has_next_step=false;
        for(int i=0; i<4; i++)
        {
            // ratb begin walk by path order
            int tempf=position.floor;
            int tempx=position.row+bmove[i].vert;
            int tempy=position.col+bmove[i].horiz;
            if( is_bounded(tempx,tempy)&&map[tempf][tempx][tempy]!=0&&bmark[tempf][tempx][tempy]==false)
            {
                //the ratb pass by the path should be recond
                bmark[tempf][tempx][tempy]=true;
                if(map[tempf][tempx][tempy]==2&&tempf==1)
                    //it is  differentiate stair. If it is a stair ,the rat must into the stair.
                    //save the x,y coordinates enter the stack a and mark the path
                {
                    element next_step= {0,tempx,tempy};
                    stackB[btop++]=next_step;
                    bmark[0][tempx][tempy]=true;
                    has_next_step=true;
                }
                else
                {
                    //If it is no a stair,direcrly the x,y coordinates enter the satack and mark the path
                    element next_step= {tempf,tempx,tempy};
                    stackB[btop++]=next_step;

                    has_next_step=true;

                }
                break;
            }
        }
        // if ratb the path meet the wall,step by step will stack atop--
        if(has_next_step==false)
            btop--;
        if (is_same_location(stackA[atop - 1], stackB[btop - 1]))
        {
            printf("ratA(%d,%d,%d)\n", stackA[atop - 1].floor, stackA[atop - 1].row,
                   stackA[atop - 1].col);
            printf("rats encounter each other in (%d,%d,%d)\n", stackA[atop - 1].floor,
                   stackA[atop - 1].row, stackA[atop - 1].col);
            break;
        }
        else if (is_A_dest(stackA[atop - 1]))
        {

            printf("rats didn't encounter each other in this maze\n");
            break;
        }
        else if (is_B_dest(stackB[btop - 1]))
        {

            printf("ratA(%d,%d,%d)\n", stackA[atop - 1].floor, stackA[atop - 1].row,
                   stackA[atop - 1].col);
            printf("rats didn't encounter each other in this maze\n");
            break;
        }
        else
        {
            printf("ratA(%d,%d,%d)\n", stackA[atop - 1].floor, stackA[atop - 1].row,
                   stackA[atop - 1].col);
            printf("ratB(%d,%d,%d)\n", stackB[btop - 1].floor, stackB[btop - 1].row,
                   stackB[btop - 1].col);
        }
    }
    return 0;
}





