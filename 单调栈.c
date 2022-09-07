#include<stdio.h>
int stack[3000001], a[3000001], f[3000001], top = 0;
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	for (int i = n; i >= 1; i--)
	{
		while (top != 0 && a[stack[top]] <= a[i])	top--;
		f[i] = top ? stack[top] : 0;
		stack[++top] = i;
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", f[i]);
	return 0;
}
