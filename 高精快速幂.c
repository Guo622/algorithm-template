#include<stdio.h>
#include<math.h>
int a[1001] = { 0 }, b[1001] = { 0 };
void fun1(void)
{
	int c[1001] = { 0 };
	for (int i = 1; i <= 500; i++)
		for (int j = 1; j <= 500; j++)
			c[i + j - 1] += a[i] * b[j];
	for (int i = 1; i <= 500; i++)
	{
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	for (int i = 1;i <= 500;i++)
		b[i] = c[i];
}
void fun2(void)
{
	int c[1001] = { 0 };
	for (int i = 1; i <= 500; i++)
		for (int j = 1; j <= 500; j++)
			c[i + j - 1] += a[i] * a[j];
	for (int i = 1; i <= 500; i++)
	{
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	for (int i = 1; i <= 500; i++)
		a[i] = c[i];
}
int main()
{
	int  p;
	scanf("%d", &p);
	printf("%d\n", (int)(1 + p * log10(2)));
	b[1] = 1; a[1] = 2;
	while (p != 0)
	{
		if (p % 2 == 1)	fun1();
		fun2();
		p /= 2;
	}
	b[1] -= 1;
	for (int i = 500; i >= 1; i--)
	{
		printf("%d", b[i]);
		if (i % 50 == 1)	putchar('\n');
	}
	return 0;
}
