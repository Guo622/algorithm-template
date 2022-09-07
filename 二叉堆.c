#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType* Elements;
} *PriorityQueue;

PriorityQueue Initialize(int MaxElements)
//初始化
{
    PriorityQueue H;
    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    H->Elements = (ElementType*)malloc((MaxElements + 1) * sizeof(ElementType));
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = INT_MIN;
    return H;
}

void Insert(ElementType X, PriorityQueue H)
//插入（上滤）
{
    int i;
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
//删除（下滤）
{
    int i, child;
    ElementType MinElement, LastElement;
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];
    for (i = 1; i * 2 <= H->Size; i = child)
    {
        child = 2 * i;
        if (child != H->Size && H->Elements[child + 1] < H->Elements[child])
            child++;
        if (LastElement > H->Elements[child])
            H->Elements[i] = H->Elements[child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

PriorityQueue BuildHeap(ElementType T[], int N)
//构建，参数T为无序树
{
    PriorityQueue H;
    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    int i, j, child, x;
    for (i = N / 2; i > 0; i--)
    {
        x = T[i];
        for (j = i; j * 2 <= N; j = child)
        {
            child = j * 2;
            if (child != N && T[child + 1] < T[child])
                child++;
            if (x > T[child])
                T[j] = T[child];
            else
                break;
        }
        T[j] = x;
    }
    H->Elements = T;
    H->Size = N;
    return H;
}

int main()
{
    int t[] = { 0, 150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130 };
    PriorityQueue H = BuildHeap(t, 15);
    for (int i = 1; i <= 15; i++)
        printf("%d ", t[i]);
    return 0;
}