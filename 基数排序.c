#include <stdio.h>
typedef struct
{
    int key[10];
    int next;
} node;
void distribute(int f[], int e[], node a[], int i)
{
    int j = a[0].next;
    for (; j; j = a[j].next)
    {
        int k = a[j].key[i];
        if (!f[k])
            f[k] = j;
        else
            a[e[k]].next = j;
        e[k] = j;
    }
}
void collect(int f[], int e[], node a[], int i)
{
    int j = 0;
    while (!f[j])
        j++;
    a[0].next = f[j];
    while (j < 10)
    {
        int k = j + 1;
        while (k < 10 && !f[k])
            k++;
        if (k == 10)
            break;
        a[e[j]].next = f[k];
        j = k;
    }
    a[e[j]].next = 0;
}
int main()
{
    node a[11] = {{{0}, 1},
                  {{2, 7, 8}, 2},
                  {{1, 0, 9}, 3},
                  {{0, 6, 3}, 4},
                  {{9, 3, 0}, 5},
                  {{5, 8, 9}, 6},
                  {{1, 8, 4}, 7},
                  {{5, 0, 5}, 8},
                  {{2, 6, 9}, 9},
                  {{0, 0, 8}, 10},
                  {{0, 8, 3}, 0}};
    for (int i = 2; i >= 0; i--)
    {
        int f[10] = {0};
        int e[10] = {0};
        distribute(f, e, a, i);
        collect(f, e, a, i);
    }
    for (int i = a[0].next; i; i = a[i].next)
    {
        printf("%d%d%d  ", a[i].key[0], a[i].key[1], a[i].key[2]);
    }
    return 0;
}