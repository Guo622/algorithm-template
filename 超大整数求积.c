#include<stdio.h>
#include<string.h>
#define N 200
int main()
{
    char A[N], B[N];
    int i, j, carry = 0, flag = 0, l1, l2, a[N], b[N], c[N][N], d[N];
    for (i = 0;i < N;i++)
        *(d + i) = 0;
    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            *(*(c + i) + j) = 0;
    gets(A);
    gets(B);
    l1 = strlen(A);
    l2 = strlen(B);
    for (i = 0;i < l1;i++)
        *(a + l1 - 1 - i) = *(A + i) - '0';
    for (i = l1;i < N;i++)
        *(a + i) = 0;
    for (i = 0;i < l2;i++)
        *(b + l2 - 1 - i) = *(B + i) - '0';
    for (i = l2;i < N;i++)
        *(b + i) = 0;
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
        {
            *(*(c + i) + (j + i)) = *(a + j) * *(b + i) + carry;
            carry = (*(*(c + i) + (j + i)) - *(*(c + i) + (j + i)) % 10) / 10;
            *(*(c + i) + (j + i)) %= 10;
        }
    }
    for (i = 0, carry = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
            *(d + i) += *(*(c + j) + i);
        *(d + i) += carry;
        carry = (*(d + i) - *(d + i) % 10) / 10;
        *(d + i) %= 10;
        *(d + i) += '0';
    }
    for (i = N - 1;i >= 0;i--)
    {
        if (flag == 0 && *(d + i) != '0')  flag = 1;
        if (flag == 1) putchar(*(d + i));
    }
    return 0;
}

void mul(string& x, string& y) {
    if (x[0] == '0' || y[0] == '0') {
        cout << 0;
        return;
    }
    int a[2005] = { 0 };
    int b[2005] = { 0 };
    int c[4005] = { 0 };
    int xl = x.length(), yl = y.length();
    for (int i = 0;i < xl;i++)
        a[i] = x[xl - 1 - i] - '0';
    for (int i = 0;i < yl;i++)
        b[i] = y[yl - 1 - i] - '0';
    for (int i = 0;i < xl;i++) {
        for (int j = 0;j < yl;j++) {
            c[i + j] += b[j] * a[i];
        }
    }
    int carry = 0;
    int i;
    for (i = 0;;i++) {
        if (c[i] == 0) break;
        c[i] += carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }
    if (carry != 0) c[i] += carry;
    else i--;
    for (;i >= 0;i--)
        cout << c[i];
}