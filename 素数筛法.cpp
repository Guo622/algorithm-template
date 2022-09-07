#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<unordered_set>
using namespace std;

bool f[1000] = { 0 };
int a[1000];
int cnt = 0, n, q;

//欧拉筛法
void sushu() {
    f[1] = 1;
    for (int i = 2;i <= n;i++) {
        if (f[i] == 0)
            a[++cnt] = i;
        for (int j = 1;j <= cnt && i * a[j] <= n;j++) {
            f[i * a[j]] = 1;
            if (i % a[j] == 0)
                break;
        }
    }
}

//埃氏筛法
// void sushu() {
//     for (long long i = 2;i <= n;i++) {
//         if (f[i] == 0) {
//             a[++cnt] = i;
//             for (long long j = i * i;j <= n;j += i)
//                 f[j] = 1;
//         }
//     }
// }

int main() {
    scanf("%d %d", &n, &q);
    sushu();
    int k;
    for (int i = 1;i <= q;i++) {
        scanf("%d", &k);
        printf("%d\n", a[k]);
    }
    return 0;
}