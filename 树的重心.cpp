#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;

//洛谷P1364

struct node { int to, next = 0; };
node edg[205];
int head[205] = { 0 }, w[205], s[205];
int cnt = 0, n;
long long ans = 0x7fffffffffffffff, dp[205];

void add(int from, int to) {
    edg[++cnt].to = to;
    edg[cnt].next = head[from];
    head[from] = cnt;
}

void dfs(int u, int f, int dep) {
    s[u] = w[u];
    for (int i = head[u];i;i = edg[i].next) {
        if (edg[i].to != f) {
            dfs(edg[i].to, u, dep + 1);
            s[u] += s[edg[i].to];
        }
    }
    dp[1] += w[u] * dep;
}
void trans(int u, int f) {
    for (int i = head[u];i;i = edg[i].next) {
        if (edg[i].to != f) {
            dp[edg[i].to] = dp[u] + s[1] - s[edg[i].to] * 2;
            trans(edg[i].to, u);
        }
    }
    ans = min(ans, dp[u]);
}
int main() {
    scanf("%d", &n);
    int u, v;
    for (int i = 1;i <= n;i++) {
        scanf("%d %d %d", &w[i], &u, &v);
        if (u) { add(i, u); add(u, i); }
        if (v) { add(i, v); add(v, i); }
    }
    dfs(1, 0, 0);
    trans(1, 0);
    printf("%lld\n", ans);
    return 0;
}