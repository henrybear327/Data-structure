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

    // 讀地圖
    read_maze();

    // 輸出地圖
    const char conversion_to_maze[3] = {'X', '.', 'o'};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < MAZE_ROW; j++) {
            for (int k = 0; k < MAZE_COL; k++) {
                printf("%c", conversion_to_maze[maze[i][j][k]]);
            }
            printf("\n");
        }
    }

    // 初始化: 把起始位置丟進stack
    State ratA = {0, 1, 1};
    State ratB = {1, 99, 99};

    posA = posB = 0;
    stackA[posA++] = ratA;
    stackB[posB++] = ratB;
    visitedA[0][1][1] = visitedB[1][99][99] = true; // 起始位置要記得記成為已經走訪過！

    // 迴圈將於任一隻老鼠到達終點或是他們相遇時停止
    while (1) {
        State curr;

        // 先動老鼠A
        
        // 我偷懶沒像課本一樣包裝stack的push pop成一個函數，所以在這裡直接檢查
        if (posA == 0) {
            printf("Empty stack A! Something is wrong!\n");
            return 0;
        }

        // 把stack最頂端的那個位置，也就是老鼠現在的位置，拿出來
        curr = stackA[posA - 1]; 
        bool has_next_step = false; // 後面有說明

        for (int i = 0; i < 4; i++) {
            // 利用剛剛從stack拿出來的老鼠現在位置，按照順序試試看下一步可以往哪裡走
            int tmpf = curr.f;
            int tmpx = curr.x + dirA[i][0];
            int tmpy = curr.y + dirA[i][1];
            
            // 只要是符合三個條件的: 在迷宮裡、不是牆壁、走訪過的地方，都是老鼠下一步可以走去的地方
            // 依此只要都符合，就準備丟進stack裡面，成為下一步!
            if (is_bounded(tmpx, tmpy) && maze[tmpf][tmpx][tmpy] != WALL &&
                visitedA[tmpf][tmpx][tmpy] == false) {
                // 記得，只要走過，都要標記為已經走訪
                visitedA[tmpf][tmpx][tmpy] = true; 

                // 檢查看看這個準備被丟進stack的地點是不是樓梯。 如果是，還要檢查看看這隻老鼠能不能走這個樓梯! 
                // (我的意思是，像說A老鼠只能上樓，所以如果他已經在樓上，他就不能再走樓梯下樓囉!)
                if (maze[tmpf][tmpx][tmpy] == STAIR && tmpf == 0) {
                    // 將走完樓梯的位置push到stack，才符合題意
                    State next_step = {1, tmpx, tmpy};
                    stackA[posA++] = next_step;
                    
                    // 標記一下走完樓梯的點為已經走訪過!
                    visitedA[1][tmpx][tmpy] = true; 
                
                    has_next_step = true;
                } else {
                    // 如果不是樓梯，就不用麻煩了! 直接push進去stack!
                    State next_step = {tmpf, tmpx, tmpy};
                    stackA[posA++] = next_step; 
                    
                    has_next_step = true;
                }
                break;
            }
        }

        if (has_next_step == false) 
            // 假設老鼠的周遭都是已經走訪過的、或是牆壁等等，造成死路一條，那就要往回走一步囉!
            // 因此，只要pop掉stack目前的這一步，就可以回到上一步啦!
            posA--;

        // B老鼠的code和A是一樣的，我懶惰所以沒改成function

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
        // 印結果的部分，就是按照助教的測資就是了，哀~~
        if (is_same_location(stackA[posA - 1], stackB[posB - 1])) {
            // 如果相遇了，就印出A座標和相遇的訊息
            // if at same location, print A location and the message
            printf("ratA(%d,%d,%d)\n", stackA[posA - 1].f, stackA[posA - 1].x,
                   stackA[posA - 1].y);
            printf("rats encounter each other in (%d,%d,%d)\n", stackA[posA - 1].f,
                   stackA[posA - 1].x, stackA[posA - 1].y);
            break;
        } else if (is_A_dest(stackA[posA - 1])) {
            // 如果A到達了終點，那就直接印出沒有相遇的訊息
            // if reaches A, then just print the message
            printf("rats didn't encounter each other in this maze\n");
            break;
        } else if (is_B_dest(stackB[posB - 1])) {
            // 如果B到達了終點，那就印出A的座標，並且印出沒有相遇的訊息
            // if reaches B, print A's location and the message
            printf("ratA(%d,%d,%d)\n", stackA[posA - 1].f, stackA[posA - 1].x,
                   stackA[posA - 1].y);
            printf("rats didn't encounter each other in this maze\n");
            break;
        } else {
            // 其餘狀況就直接印出A B的座標即可，並且繼續執行!
            // just print both A and B's location
            printf("ratA(%d,%d,%d)\n", stackA[posA - 1].f, stackA[posA - 1].x,
                   stackA[posA - 1].y);
            printf("ratB(%d,%d,%d)\n", stackB[posB - 1].f, stackB[posB - 1].x,
                   stackB[posB - 1].y);
        }
    }

    return 0;
}
