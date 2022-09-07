#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int weight;
    int parent, lchild, rchild;
} HTNode, * HuffmanTree;

typedef char** HuffmanCode;

void Select(HuffmanTree HT, int i, int& s1, int& s2)
{
    HTNode* p = HT + 1;
    int min1, min2;
    min1 = min2 = INT_MAX;
    for (int j = 1; j <= i; j++, p++)
    {
        if (p->parent != 0)
            continue;
        if (p->weight < min1)
        {
            min2 = min1;
            min1 = p->weight;
            s2 = s1;
            s1 = j;
            continue;
        }
        if (p->weight < min2)
        {
            min2 = p->weight;
            s2 = j;
        }
    }
}
void HuffmanCodeing(HuffmanTree& HT, HuffmanCode& HC, int* w, int n)
{
    if (n <= 1)    return;
    int m = 2 * n - 1, i, c, f;
    int s1, s2, start;
    HTNode* p;
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
    for (p = HT + 1, i = 1; i <= n; i++, p++, w++)        *p = { *w, 0, 0, 0 };
    for (; i <= m; i++, p++)        *p = { 0, 0, 0, 0 };
    for (i = n + 1; i <= m; i++)
    {
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;    HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }    //构建赫夫曼树

    //从叶子节点到根逆向求每个字符的赫夫曼编码
    HC = (HuffmanCode)malloc(sizeof(char*) * (n + 1));
    char* cd = (char*)malloc(sizeof(char) * n);
    cd[n - 1] = '\0';
    for (i = 1; i <= n; i++)
    {
        start = n - 1;
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
        {
            if (HT[f].lchild == c)      cd[--start] = '0';
            else        cd[--start] = '1';
        }
        HC[i] = (char*)malloc((n - start) * sizeof(char));
        strcpy(HC[i], cd + start);
    }
    free(cd);
}

int main()
{
    HuffmanTree HT = NULL;
    int w[8] = { 5, 29, 7, 8, 14, 23, 3, 11 };
    int n = 8;
    HuffmanCode HC = NULL;
    HuffmanCodeing(HT, HC, w, n);
    for (int i = 1; i <= n; i++)
        printf("%s\n", HC[i]);
    return 0;
}