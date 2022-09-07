#include <stdio.h>
void mergesort(int a[], int left, int right)
{
    if (left == right)
        return;
    int mid = left + right >> 1;
    mergesort(a, left, mid);
    mergesort(a, mid + 1, right);
    int i = left, j = mid + 1, k = left;
    int t[right + 1];
    while (i <= mid && j <= right)
    {
        if (a[i] < a[j])
            t[k++] = a[i++];
        else
            t[k++] = a[j++];
    }
    while (i <= mid)
        t[k++] = a[i++];
    while (j <= right)
        t[k++] = a[j++];
    for (i = left; i <= right; i++)
        a[i] = t[i];
}

void merge(int a[], int p, int q, int r) {
    int i = p, j = q + 1, k = 0;
    int* b = new int(r - p + 1);
    while (i <= q && j <= r) {
        if (a[i] < a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    }
    while (i <= q) b[k++] = a[i++];
    while (j <= r) b[k++] = a[j++];
    for (int x = p;x <= r;x++)
        a[x] = b[x - p];
    delete[]b;
}

void mergesort(int a[], int p, int r) {
    if (p < r) {
        int q = p + r >> 1;
        mergesort(a, p, q);
        mergesort(a, q + 1, r);
        merge(a, p, q, r);
    }
}
int main()
{
    int a[] = { 0, 12, 32, 431, 43, 31, 67, 56, 90, 79, 10 };
    mergesort(a, 1, 10);
    for (int i = 1; i <= 10; i++)
        printf("%d ", a[i]);
    return 0;
}