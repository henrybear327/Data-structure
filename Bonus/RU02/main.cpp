#include <cstdio>

int ans;
int X, Y, N, x, y, w, h;

void explosion(int xc, int yc, int nc) // pass in new center
{
    // printf("%d %d %d\n", xc, yc, nc);
    if (xc - nc / 2 <= x + w && yc - nc / 2 <= y + h && xc + nc / 2 >= x &&
        yc + nc / 2 >= y) {
        // guaranteed to have solutions
        int x_r_bound = xc + nc / 2 - (x + w) >= 0 ? x + w : xc + nc / 2;
        int x_l_bound = x - (xc - nc / 2) >= 0 ? x : xc - nc / 2;
        int y_u_bound = yc + nc / 2 - (y + h) >= 0 ? y + h : yc + nc / 2;
        int y_l_bound = y - (yc - nc / 2) >= 0 ? y : yc - nc / 2;

        ans += ((x_r_bound - x_l_bound + 1) * (y_u_bound - y_l_bound + 1) * nc);
    }

    if (nc == 2)
        return;
    // printf("r %d %d %d\n", xc, yc, nc);
    explosion(xc + 3 * nc / 4, yc, nc / 2);
    // printf("d %d %d %d\n", xc, yc, nc);
    explosion(xc, yc - 3 * nc / 4, nc / 2);
    // printf("l %d %d %d\n", xc, yc, nc);
    explosion(xc - 3 * nc / 4, yc, nc / 2);
    // printf("r %d %d %d\n", xc, yc, nc);
    explosion(xc, yc + 3 * nc / 4, nc / 2);
}

int main()
{
    while (scanf("%d %d %d %d %d %d %d", &X, &Y, &N, &x, &y, &w, &h) == 7) {
        ans = 0;
        explosion(X, Y, N);

        printf("%d\n", ans);
    }

    return 0;
}
