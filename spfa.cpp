#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<unordered_map>

using namespace std;

struct edg {
    int to, next = 0;
    int w;
}e[500002];

int n, m, s, d[10002];
int cnt = 0, head[10002] = { 0 };
bool vis[10002] = { 0 };

void add(int from, int to, int w) {
    e[++cnt].next = head[from];
    e[cnt].to = to;
    e[cnt].w = w;
    head[from] = cnt;
}

void spfa() {
    fill(d + 1, d + 1 + n, 2147483647);
    d[s] = 0;
    queue<int>q;
    q.push(s); vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();q.pop();
        vis[u] = 0;
        for (int i = head[u];i;i = e[i].next) {
            int v = e[i].to;
            if (d[v] > d[u] + e[i].w) {
                d[v] = d[u] + e[i].w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1;i <= m;i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add(u, v, w);
    }
    spfa();
    for (int i = 1;i <= n;i++)
        printf("%d ", d[i]);
    return 0;
}