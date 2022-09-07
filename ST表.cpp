#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<unordered_map>
using namespace std;

//洛谷P3865

inline int read()
{
    int x = 0, f = 1;char ch = getchar();
    while (ch < '0' || ch>'9') { if (ch == '-') f = -1;ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - 48;ch = getchar(); }
    return x * f;
}

int main() {
    int m, n;
    int st[100005][21] = { 0 };
    n = read(), m = read();
    for (int i = 1;i <= n;i++)
        st[i][0] = read();
    for (int j = 1;j <= 21;j++) {
        for (int i = 1;i + (1 << j) - 1 <= n;i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    while (m--) {
        int l = read(), r = read();
        int k = log2(r - l + 1);
        printf("%d\n", max(st[l][k], st[r - (1 << k) + 1][k]));
    }
    return 0;
}