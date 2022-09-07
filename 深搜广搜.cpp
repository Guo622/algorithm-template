#include<stdio.h>
#include<string.h>
typedef struct
{
    int adj;
    int next;
}arcnode;

int flag[100001] = { 0 }, head[100001] = { 0 };
arcnode arc[1000001];
int n, m, x, y;

void dfs(int i)
{
    flag[i]++;
    printf("%d ", i);
    for (int j = head[i];j;j = arc[j].next)
        if (flag[arc[j].adj] == 0)
            dfs(arc[j].adj);
}

void bfs()
{
    int queue[100002], front = 0, tail = 0, i, j, k;
    for (i = 1;i <= n;i++)
        if (flag[i] == 0)
        {
            flag[i]++;
            printf("%d ", i);
            queue[tail++] = i;
            while (front != tail)
            {
                j = queue[front++];
                for (k = head[j];k;k = arc[k].next)
                    if (flag[arc[k].adj] == 0)
                    {
                        flag[arc[k].adj]++;
                        printf("%d ", arc[k].adj);
                        queue[tail++] = arc[k].adj;
                    }
            }
        }
}

int main()
{
    int i, j;
    scanf("%d %d", &n, &m);
    for (i = 1;i <= m;i++)
    {
        scanf("%d %d", &x, &y);
        arc[i].adj = y, arc[i].next = 0;
        if (head[x] == 0)
            head[x] = i;
        else
        {
            for (j = head[x];arc[j].next;j = arc[j].next);
            arc[j].next = i;
        }
    }
    for (i = 1;i <= n;i++)
        if (flag[i] == 0)
            dfs(i);
    printf("\n");
    memset(flag + 1, 0, n * sizeof(int));
    bfs();
    return 0;
}