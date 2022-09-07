#include<iostream>
#include<cstdio>
#include<algorithm>

//https://www.cnblogs.com/dijkstra2003/p/9676729.html

using ll = long long;
using namespace std;
const int maxn = 100001;
ll n, m, mod;

struct node {
    ll left, right, sum, ptag = 0, mtag = 1;
}tree[maxn << 2];
ll a[maxn];

inline ll ls(ll i) { return i << 1; }
inline ll rs(ll i) { return i << 1 | 1; }

inline void push_up(ll p) {
    tree[p].sum = (tree[ls(p)].sum + tree[rs(p)].sum) % mod;
}

inline void build(ll left, ll right, ll p) {
    tree[p].left = left;
    tree[p].right = right;
    if (left == right) { tree[p].sum = a[left] % mod; return; }
    ll mid = left + right >> 1;
    build(left, mid, ls(p));
    build(mid + 1, right, rs(p));
    push_up(p);
}

inline void func(ll p, ll k1, ll k2) {
    tree[p].sum = (tree[p].sum * k2 + k1 * (tree[p].right - tree[p].left + 1)) % mod;
    tree[p].mtag = (tree[p].mtag * k2) % mod;
    tree[p].ptag = (tree[p].ptag * k2 + k1) % mod;
}

inline void push_down(ll p) {
    func(ls(p), tree[p].ptag, tree[p].mtag);
    func(rs(p), tree[p].ptag, tree[p].mtag);
    tree[p].ptag = 0; tree[p].mtag = 1;
}

inline void add(ll left, ll right, ll p, ll k) {
    if (left <= tree[p].left && tree[p].right <= right) {
        tree[p].sum += (k * (tree[p].right - tree[p].left + 1)) % mod;
        tree[p].ptag = (tree[p].ptag + k) % mod;
        return;
    }
    push_down(p);
    if (tree[ls(p)].right >= left) add(left, right, ls(p), k);
    if (tree[rs(p)].left <= right) add(left, right, rs(p), k);
    push_up(p);
}

inline void mul(ll left, ll right, ll p, ll k) {
    if (left <= tree[p].left && tree[p].right <= right) {
        tree[p].sum = (tree[p].sum * k) % mod;
        tree[p].mtag = (tree[p].mtag * k) % mod;
        tree[p].ptag = (tree[p].ptag * k) % mod;
        return;
    }
    push_down(p);
    if (tree[ls(p)].right >= left) mul(left, right, ls(p), k);
    if (tree[rs(p)].left <= right) mul(left, right, rs(p), k);
    push_up(p);
}

inline ll query(ll left, ll right, ll p) {
    ll ans = 0;
    if (tree[p].right<left || tree[p].left>right) return 0;
    if (left <= tree[p].left && tree[p].right <= right) return tree[p].sum;
    push_down(p);
    if (tree[ls(p)].right >= left) ans += query(left, right, ls(p)) % mod;
    if (tree[rs(p)].left <= right) ans += query(left, right, rs(p)) % mod;
    return ans % mod;
}

int main() {
    scanf("%lld %lld %lld", &n, &m, &mod);
    for (int i = 1;i <= n;i++)
        scanf("%lld", a + i);
    build(1, n, 1);
    int op;
    while (m--) {
        scanf("%d", &op);
        if (op == 1) {
            ll x, y, k;
            scanf("%lld %lld %lld", &x, &y, &k);
            mul(x, y, 1, k % mod);
        }
        else if (op == 2) {
            ll x, y, k;
            scanf("%lld %lld %lld", &x, &y, &k);
            add(x, y, 1, k % mod);
        }
        else {
            ll x, y;
            scanf("%lld %lld", &x, &y);
            printf("%lld\n", query(x, y, 1));
        }
    }
    return 0;
}



// 纯加减
// #include<iostream>
// #include<cstdio>
// #include<algorithm>
// using ll = long long;
// using namespace std;
// const int maxn = 100001;
// ll n, m;

// // 加减
// struct node {
//     ll left, right, sum, tag;
// }tree[maxn << 2];
// ll a[maxn];

// inline ll ls(ll i) { return i << 1; }
// inline ll rs(ll i) { return i << 1 | 1; }

// inline void push_up(ll p) {
//     tree[p].sum = tree[ls(p)].sum + tree[rs(p)].sum;
// }

// void build(ll left, ll right, ll p) {
//     tree[p].tag = 0;
//     tree[p].left = left;
//     tree[p].right = right;
//     if (left == right) { tree[p].sum = a[left]; return; }
//     ll mid = left + right >> 1;
//     build(left, mid, ls(p));
//     build(mid + 1, right, rs(p));
//     push_up(p);
// }

// inline void func(ll p, ll k) {
//     tree[p].tag += k;
//     tree[p].sum += k * (tree[p].right - tree[p].left + 1);
// }

// inline void push_down(ll p) {
//     func(ls(p), tree[p].tag);
//     func(rs(p), tree[p].tag);
//     tree[p].tag = 0;
// }

// inline void update(ll left, ll right, ll p, ll k) {
//     if (left <= tree[p].left && tree[p].right <= right) {
//         tree[p].sum += k * (tree[p].right - tree[p].left + 1);
//         tree[p].tag += k;
//         return;
//     }
//     push_down(p);
//     if (tree[ls(p)].right >= left) update(left, right, ls(p), k);
//     if (tree[rs(p)].left <= right) update(left, right, rs(p), k);
//     push_up(p);
// }

// ll query(ll left, ll right, ll p) {
//     ll ans = 0;
//     if (left <= tree[p].left && tree[p].right <= right) return tree[p].sum;
//     push_down(p);
//     if (tree[ls(p)].right >= left) ans += query(left, right, ls(p));
//     if (tree[rs(p)].left <= right) ans += query(left, right, rs(p));
//     return ans;
// }

// int main() {
//     scanf("%lld %lld", &n, &m);
//     for (int i = 1;i <= n;i++)
//         scanf("%lld", a + i);
//     build(1, n, 1);
//     int op;
//     while (m--) {
//         scanf("%d", &op);
//         if (op == 1) {
//             ll x, y, k;
//             scanf("%lld %lld %lld", &x, &y, &k);
//             update(x, y, 1, k);
//         }
//         else {
//             ll x, y;
//             scanf("%lld %lld", &x, &y);
//             printf("%lld\n", query(x, y, 1));
//         }
//     }
//     return 0;
// }


