#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<unordered_map>


using namespace std;
int main() {
    const int inf = 0x7fffffff;
    const int maxn = 100001;
    int a[maxn], b[maxn], r[maxn];
    vector<int>q(maxn, inf);
    int n;
    scanf("%d", &n);
    for (int i = 1;i <= n;i++) {
        scanf("%d", &a[i]);
        r[a[i]] = i;
    }
    for (int i = 1;i <= n;i++) {
        scanf("%d", &b[i]);
    }
    int len = 0;
    q[0] = 0;
    for (int i = 1;i <= n;i++) {
        if (r[b[i]] > q[len]) q[++len] = r[b[i]];
        else {
            vector<int>::iterator iter = upper_bound(q.begin(), q.begin() + len + 1, r[b[i]]);
            *iter = r[b[i]];
        }
    }
    printf("%d", len);
    return 0;
}
