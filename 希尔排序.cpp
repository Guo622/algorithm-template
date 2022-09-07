#include <stdio.h>
void shellinsert(int a[], int dk, int len)
{
    int i, j;
    for (i = dk + 1; i <= len; i++)
    {
        if (a[i] < a[i - dk])
        {
            a[0] = a[i];
            for (j = i - dk; j > 0 && a[0] < a[j]; j -= dk)
                a[j + dk] = a[j];
            a[j + dk] = a[0];
        }
    }
}
void shellsort(int a[], int dlta[], int t, int len)
{
    for (int i = 0; i < t; i++)
        shellinsert(a, dlta[i], len);
}
int main()
{
    int a[11] = { 0, 12, 312, 11, 32, 43, 14, 54, 2, 10, 100 };
    int dlat[] = { 5, 3, 1 };
    shellsort(a, dlat, 3, 10);
    for (int i = 1; i <= 10; i++)
        printf("%d ", a[i]);
}
