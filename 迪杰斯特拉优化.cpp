#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<unordered_map>

using namespace std;

struct node {
    int v, dis;
    bool operator <(const node& b)const {
        return dis > b.dis;
    }
};

struct edg {
    int to, next = 0, w;
}e[100];

priority_queue<node>q;
int n, m, s;
int d[100], vis[100] = { 0 };
int cnt = 0, head[100] = { 0 };

void add(int from, int to, int w) {
    e[++cnt].next = head[from];
    e[cnt].to = to;
    e[cnt].w = w;
    head[from] = cnt;
}

void dijkstra() {
    fill(d + 1, d + 1 + n, 0x7fffffff);
    d[s] = 0;
    q.push({ s,0 });
    while (!q.empty()) {
        int u = q.top().v; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u];i;i = e[i].next) {
            int v = e[i].to;
            if (!vis[v] && d[v] > d[u] + e[i].w) {
                d[v] = e[i].w + d[u];
                q.push({ v,d[v] });
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
    dijkstra();
    for (int i = 1;i <= n;i++)
        printf("%d ", d[i]);
    return 0;
}
/*
#include<stdio.h>
#define MAX       2147483647

typedef struct arcnode
{
    int next;
    int adj, weight;
}arcnode;
typedef struct heapnode
{
    int dis;
    int pos;
} priority_queue;

void insert(priority_queue q[], heapnode h, int& size)
{
    int i;
    for (i = ++size;q[i / 2].dis > h.dis;i /= 2)
        q[i] = q[i / 2];
    q[i] = h;
}

heapnode deletemin(priority_queue q[], int& size)
{
    int i, child;
    heapnode min, last;
    min = q[1], last = q[size--];
    for (i = 1;i * 2 <= size;i = child)
    {
        child = 2 * i;
        if (child != size && q[child + 1].dis < q[child].dis)
            child++;
        if (last.dis > q[child].dis)
            q[i] = q[child];
        else    break;
    }
    q[i] = last;
    return min;
}

int main()
{
    arcnode arc[20001];
    priority_queue q[10001], h;
    int head[10001] = { 0 }, size = 0;
    int n, m, s, u, v, w, d[10001], flag[10001] = { 0 };
    int i, j, k;
    scanf("%d %d %d", &n, &m, &s);
    for (i = 1;i <= m;i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        arc[i].adj = v, arc[i].weight = w;
        arc[i].next = head[u];
        head[u] = i;
    }
    for (i = 1;i <= n;i++)
        d[i] = MAX;
    d[s] = 0;
    insert(q, { 0,s }, size);
    while (size)
    {
        h = deletemin(q, size);
        i = h.pos;
        if (flag[i])  continue;
        flag[i]++;
        for (j = head[i];j;j = arc[j].next)
        {
            k = arc[j].adj;
            if (arc[j].weight + d[i] < d[k])
            {
                d[k] = arc[j].weight + d[i];
                if (!flag[k])
                    insert(q, { d[k],k }, size);
            }
        }
    }
    for (i = 1;i <= n;i++)
        printf("%d ", d[i]);
    return 0;
}
*/