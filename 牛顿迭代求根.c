#include<stdio.h>
#include<math.h>
int main()
{
	double a, b, c, d;
	double f0, f1, x0, x1;
	int s=0;
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	for (x1 = -100;; )
	{
		do
		{
			x0 = x1;
			f0 = x0 * (x0 * (a * x0 + b) + c) + d;
			f1 = x0 * (3 * a * x0 + 2 * b) + c;
			x1 = x0 - f0 / f1;
		} while (fabs(x1 - x0) >= 1e-3);
		printf("%.2lf ", x1);
		s++;
		if (s == 1) x1 = -b / (3 * a);
		if (s == 2) x1 = 100;
		if (s == 3) break;

	}
	return 0;
}
