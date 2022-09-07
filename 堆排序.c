#include <stdio.h>
void heapadjust(int a[], int s, int m)
{
    int key = a[s];
    int j;
    for (j = 2 * s; j <= m; j *= 2)
    {
        if (j < m&& a[j] < a[j + 1])
            j++;
        if (key >= a[j])
            break;
        a[s] = a[j];
        s = j;
    }
    a[s] = key;
} //�����󶥶�
void heapsort(int a[], int len)
{
    int i;
    for (i = len / 2; i > 0; i--)
        heapadjust(a, i, len);
    for (i = len; i > 1; i--)
    {
        int t = a[i];
        a[i] = a[1];
        a[1] = t;
        heapadjust(a, 1, i - 1);
    }
}
int main()
{
    int a[] = { 0, 12, 14, 35, 13, 59, 32, 69, 58, 40, 76 };
    heapsort(a, 10);
    for (int i = 1; i <= 10; i++)
        printf("%d ", a[i]);
    return 0;
}
