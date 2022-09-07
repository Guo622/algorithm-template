#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

//洛谷P1433

int n;
double d[16][16];
double a[16][2];
double dp[16][1 << 16];
double ans = 0.0;

double dis(int i, int j) {
    return sqrt((a[i][0] - a[j][0]) * (a[i][0] - a[j][0]) + (a[i][1] - a[j][1]) * (a[i][1] - a[j][1]));
}

int pos(int i) { return 1 << (i - 1); }


int main() {
    scanf("%d", &n);
    memset(dp, 127, sizeof(dp));
    ans = dp[0][0];
    a[0][0] = a[0][1] = 0.0;
    for (int i = 1;i <= n;i++)
        scanf("%lf %lf", &a[i][0], &a[i][1]);
    for (int i = 0;i <= n;i++) {
        for (int j = i + 1;j <= n;j++)
            d[i][j] = d[j][i] = dis(i, j);
    }
    for (int i = 1;i <= n;i++)
        dp[i][pos(i)] = d[0][i];
    for (int s = 1;s < (1 << n);s++) {
        for (int i = 1;i <= n;i++) {
            if ((s & pos(i)) == 0) continue;
            for (int j = 1;j <= n;j++) {
                if (j == i) continue;
                if ((s & pos(j)) == 0) continue;
                dp[i][s] = min(dp[i][s], dp[j][s - pos(i)] + d[i][j]);
            }
        }
    }
    for (int i = 1;i <= n;i++)
        ans = min(ans, dp[i][(1 << n) - 1]);
    printf("%.2lf", ans);
    return 0;
}
