/*
Basic idea behind DFS
This code is INCOMPLETE!

https://gist.github.com/BeMg/fc15ad1c3fdb8cbc5cde
*/
#include <stdio.h>

#define N 4
int visited[N];
int connection[N][N];
int start, end;
void dfs(int current)
{
    if(current == end) {
       // do something

       return;
    }

    for(int i = 0; i < N; i++) {
        if(connection[current][i] == 1 && visited[i] == 0) {
            visited[i] = 1;
            dfs(i);
            visited[i] = 0;
        }
    }

    return;
}

int main()
{
    visited[start] = 1;
    dfs(start);

    return 0;
}
