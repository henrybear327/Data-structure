#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CAP 1000
#define DEBUG 0
int capacity, station, source, destination, edge;
int bike_in_station[MAX_CAP];
int orig[MAX_CAP][MAX_CAP];
int dist[MAX_CAP][MAX_CAP];

#define MIN(x, y) ((x) < (y) ? (x) : (y))
void floyd_warshall()
{
    for (int k = 0; k <= station; k++)
        for (int i = 0; i <= station; i++)
            for (int j = 0; j <= station; j++)
                dist[i][j] = MIN(dist[i][j], dist[i][k] + dist[k][j]);
}

int curr_path[MAX_CAP], ans_path[MAX_CAP];
int ans_path_length, ans_bike_out, ans_bike_in;
int visited[MAX_CAP];
void dfs(int curr, int level, int total_dist, int bike_out, int bike_in)
{
    if (total_dist > dist[source][destination])
        return;
    if (curr == destination) {
        if (total_dist == dist[source][destination]) {
            if (bike_out + bike_in < ans_bike_out + ans_bike_in) {
                ans_bike_out = bike_out;
                ans_bike_in = bike_in;
                ans_path_length = level;
                for (int i = 0; i < level; i++) {
                    ans_path[i] = curr_path[i];
                }
            } else if (bike_out + bike_in == ans_bike_out + ans_bike_in &&
                       level < ans_path_length) {
                ans_path_length = level;
                for (int i = 0; i < level; i++) {
                    ans_path[i] = curr_path[i];
                }
            }
        }

        return;
    }

    for (int i = 0; i <= station; i++) {
        if (orig[curr][i] != 0 && visited[i] == 0) {
            visited[i] = 1;
            curr_path[level] = i;
            int diff = bike_in_station[i] - capacity / 2;

            if (diff >= 0) {
                dfs(i, level + 1, total_dist + orig[curr][i], bike_out, bike_in + diff);
            } else {
                if (bike_in > abs(diff))
                    dfs(i, level + 1, total_dist + orig[curr][i], bike_out,
                        bike_in - abs(diff));
                else
                    dfs(i, level + 1, total_dist + orig[curr][i],
                        bike_out + abs(diff) - bike_in, 0);
            }
            visited[i] = 0;
        }
    }
}

int main()
{
    source = 0;
    scanf("%d %d %d %d", &capacity, &station, &destination, &edge);
    for (int i = 1; i <= station; i++)
        scanf("%d", &bike_in_station[i]);

    memset(orig, 0, sizeof(orig));
    for (int i = 0; i <= station; i++) {
        for (int j = 0; j <= station; j++) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = (int)1e9;
        }
    }

    for (int i = 0; i < edge; i++) {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);

        dist[from][to] = dist[to][from] = weight;
        orig[from][to] = orig[to][from] = weight;
    }

    floyd_warshall();
#if DEBUG == 1
    printf("floyd_walshall\n");
    for (int i = 0; i <= station; i++)
        for (int j = 0; j <= station; j++)
            printf("%d%c", dist[i][j], j == station ? '\n' : ' ');
    printf("\n");

    printf("connectivity\n");
    for (int i = 0; i <= station; i++)
        for (int j = 0; j <= station; j++)
            printf("%d%c", g[i][j], j == station ? '\n' : ' ');
    printf("\n");
#endif

    ans_path_length = ans_bike_out = ans_bike_in = (int)1e9;
    memset(visited, 0, sizeof(visited));
    visited[0] = 1;
    dfs(0, 1, 0, 0, 0);

    printf("%d ", ans_bike_out);
    for (int i = 0; i < ans_path_length; i++)
        printf("%d%c", ans_path[i], i == ans_path_length - 1 ? ' ' : '>');
    printf("%d\n", ans_bike_in);

    return 0;
}
