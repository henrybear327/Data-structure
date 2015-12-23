#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

/*
Greedy WA
5 10
1 2 3 4 5 6 7 8 9 10
*/

int main()
{
    int k, n;
    while (scanf("%d %d", &k, &n) == 2 && (k || n)) {
        int inp[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &inp[i]);
        }

        sort(inp, inp + n);
        reverse(inp, inp + n);

        long long int sum = 0LL;
        for (int i = 0; i < k; i++)
            sum += inp[i];
        sum /= 2; // mid of sum
    }

    return 0;
}
