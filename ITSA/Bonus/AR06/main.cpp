#include <cstdio>
#include <algorithm>

using namespace std;

typedef struct data {
    int i, j, w;
} Data;

int cmp(const void *a, const void *b)
{
   return  ((Data *)b)->w - ((Data *)a)->w;
}

int main()
{
    int n;
    
    while(scanf("%d", &n) == 1) {
	Data inp[n*n];
	for(int i = 0; i < n; i++) {
	    for(int j = 0; j < n; j++) {
		scanf("%d", &inp[i * n + j].w);
		inp[i * n + j].i = i;
		inp[i * n + j].j = j;
	    }
	}

	qsort(inp, n * n, sizeof(Data), cmp);

	book[n];
	fill(book, book + n, 0);

	for(int i = 0; i < n * n; i++) {
	    if(book[inp[i].i] == )
	}
    }

    return 0;
}
