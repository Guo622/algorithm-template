#include<stdio.h>
int n, m, a[10001];
void swap(int x, int y)
{
	int t = a[x];
	a[x] = a[y];
	a[y] = t;
}
int main()
{
	scanf("%d %d", &n, &m);
	int i, j, k;
	for (i = 1; i <= n; i++)
		scanf("%d", a + i);
	for (i = 1; i <= m; i++)
	{
		for (j = n - 1; j >= 1; j--)
			if (a[j] < a[j + 1])
				break;
		for (k = n; k >= j; k--)
			if (a[k] > a[j])
				break;
		swap(j, k);
		for (j = j + 1, k = n; k > j; j++, k--)
			swap(j, k);
	}
	for (i = 1; i <= n; i++)
		printf("%d ", a[i]);
	return 0;
}
