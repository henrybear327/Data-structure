#include <stdio.h>

int main()
{
    int capacity, station, dest, segment;
    scanf("%d %d %d %d", &capacity, &station, &dest, &segment);

    //while(station > 400);


    //while(capacity % 2 != 0);
    //while(station == 0);
    //while(dest == 0);
    //while(segment == 0);

    int cnt[station+1][station+1];
    for(int i = 0; i < station+1; i++)
        for(int j = 0; j < station+1; j++)
            cnt[i][j] = 0;
    for(int i = 0; i < station; i++) {
        int tmp;
        scanf("%d", &tmp);
    }
    for(int i = 0; i < segment; i++) {
        int f, t, w;
        scanf("%d %d %d", &f, &t, &w);

        //while(w == 0);
        //while(f == t);
        cnt[f][t]++;
        cnt[t][f]++;
        //while(cnt[f][t] > 1);
    }

    printf("0\n");

    return 0;
}
