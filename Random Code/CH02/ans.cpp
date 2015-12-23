#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    int k, n;
    while (scanf("%d %d", &k, &n)) {
        if (k == 0 && n == 0)
            break;
        int a[n];
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        sort(a, a + n, cmp);
        // for(int i=0; i<n; i++)
        //    printf("%d%c",a[i],i==n-1 ? '\n' : ' ');
        int sum = 0;
        map<int, int> mp;
        vector<int> v;
        for (int i = 0; i < k; i++) {
            sum += a[i];
        }
        int cnt = 0;
        int temp;
        int curr;
        int ans = 0;
        v.push_back(0);
        for (int i = 0; i < k; i++) {
            temp = v.size();
            cnt = 0;
            while (temp--) {
                curr = v[cnt++] + a[i];
                if (abs(curr - sum / 2) < abs(ans - sum / 2))
                    ans = curr;
                if (mp[curr] == 0) {
                    mp[curr] = 1;
                    v.push_back(curr);
                }
            }
        }
        // for(int i=0; i<v.size(); i++)
        //    printf("%d ",v[i]);
        // printf("\n");
        // printf("%lld %lld\n",s1,s2);
        printf("%d\n", ans * (sum - ans));
    }
    return 0;
}
