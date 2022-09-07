#include <stdio.h>
#include<stdlib.h>
#define max(x,y) ((x)>(y)?(x):(y))
enum { RH = -1, EH, LH };
enum { FALSE, TRUE };
typedef struct BSTNode
{
    int data, bf, num, size, height;
    struct BSTNode* lchild, * rchild;
} BSTNode, * BSTree;

int Get_Height(BSTree T) { if (T == NULL) return 0; return T->height; }

int Get_Size(BSTree T) { if (T == NULL) return 0; return T->size; }

void Update(BSTree p)
{
    int h1 = Get_Height(p->lchild), h2 = Get_Height(p->rchild);
    p->height = max(h1, h2) + 1;
    p->size = Get_Size(p->lchild) + Get_Size(p->rchild) + p->num;
}

void R_Rotate(BSTree& p)
{
    BSTree lc = p->lchild;
    p->lchild = lc->rchild; lc->rchild = p; p = lc;
    Update(p->rchild);Update(p);
}

void L_Rotate(BSTree& p)
{
    BSTree rc = p->rchild;
    p->rchild = rc->lchild; rc->lchild = p; p = rc;
    Update(p->lchild);Update(p);
}

void LeftBlance(BSTree& T)
{
    BSTree lc = T->lchild;
    switch (lc->bf)
    {
    case LH: T->bf = lc->bf = EH; R_Rotate(T); break;
    case RH:
        BSTree rd = lc->rchild;
        switch (rd->bf)
        {
        case LH: T->bf = RH; lc->bf = EH;  break;
        case EH: T->bf = lc->bf = EH; break;
        case RH: T->bf = EH; lc->bf = LH; break;
        }
        rd->bf = EH;
        L_Rotate((T->lchild));
        R_Rotate(T);
    }
}

void RightBlance(BSTree& T)
{
    BSTree rc = T->rchild;
    switch (rc->bf)
    {
    case RH: T->bf = rc->bf = EH; L_Rotate(T); break;
    case LH:
        BSTree ld = rc->lchild;
        switch (ld->bf)
        {
        case LH: T->bf = EH; rc->bf = RH; break;
        case EH: T->bf = rc->bf = EH; break;
        case RH: T->bf = LH; rc->bf = EH; break;
        }
        ld->bf = EH;
        R_Rotate(T->rchild);
        L_Rotate(T);
    }
}

void Insert(BSTree& T, int e, int& taller)
{
    if (T == NULL)
    {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->data = e;T->lchild = T->rchild = NULL;
        T->size = T->height = 1;
        T->bf = EH;T->num = 1;taller = TRUE;
        return;
    }
    if (e == T->data) { T->num++, T->size++, taller = FALSE; return; }
    if (e < T->data)
    {
        Insert(T->lchild, e, taller);
        if (taller)
            switch (T->bf)
            {
            case LH: LeftBlance(T); taller = FALSE; break;
            case EH: T->bf = LH; taller = TRUE; break;
            case RH: T->bf = EH; taller = FALSE; break;
            }
    }
    else
    {
        Insert(T->rchild, e, taller);
        if (taller)
            switch (T->bf)
            {
            case LH: T->bf = EH; taller = FALSE; break;
            case EH: T->bf = RH; taller = TRUE; break;
            case RH: RightBlance(T); taller = FALSE; break;
            }
    }
    Update(T);
}

void Delete(BSTree& p, int e, int& shorter)
{
    if (p == NULL)     return;
    BSTree q;
    if (p->data == e)
    {
        if (p->num > 1) { p->num--; shorter = FALSE; }
        else if (p->lchild == NULL) { q = p; p = p->rchild;shorter = TRUE; free(q); }
        else if (p->rchild == NULL) { q = p; p = p->lchild; shorter = TRUE;free(q); }
        else
        {
            q = p->rchild;
            while (q->lchild)    q = q->lchild;
            p->num = q->num; p->data = q->data; q->num = 1;
            Delete(p->rchild, q->data, shorter);
            if (shorter)
                switch (p->bf)
                {
                case EH:p->bf = LH;shorter = FALSE;break;
                case RH:p->bf = EH;shorter = TRUE;break;
                case LH:
                    LeftBlance(p);
                    if (Get_Height(p->lchild) <= Get_Height(p->rchild)) shorter = TRUE;
                    else shorter = FALSE;
                    break;
                }
        }
    }
    else if (p->data > e)
    {
        Delete(p->lchild, e, shorter);
        if (shorter)
            switch (p->bf)
            {
            case EH:p->bf = RH;shorter = FALSE;break;
            case LH:p->bf = EH;shorter = TRUE;break;
            case RH:
                RightBlance(p);
                if (Get_Height(p->lchild) >= Get_Height(p->rchild)) shorter = TRUE;
                else shorter = FALSE;
                break;
            }
    }
    else
    {
        Delete(p->rchild, e, shorter);
        if (shorter)
            switch (p->bf)
            {
            case EH:p->bf = LH;shorter = FALSE;break;
            case RH:p->bf = EH;shorter = TRUE;break;
            case LH:
                LeftBlance(p);
                if (Get_Height(p->lchild) <= Get_Height(p->rchild)) shorter = TRUE;
                else shorter = FALSE;
                break;
            }
    }
    if (p) Update(p);
}

int Get_Rank(BSTree T, int e)
{
    if (T->data == e)  return Get_Size(T->lchild) + 1;
    if (e < T->data)   return Get_Rank(T->lchild, e);
    return Get_Rank(T->rchild, e) + Get_Size(T->lchild) + T->num;
}

int Get_Rank_Val(BSTree T, int rank)
{
    int x = Get_Size(T->lchild);
    if (x >= rank)   return Get_Rank_Val(T->lchild, rank);
    if (x + T->num >= rank) return T->data;
    return Get_Rank_Val(T->rchild, rank - x - T->num);
}

int Get_Pre(BSTree T, int e)
{
    BSTree pre = T->lchild, p = T;
    while (p)
    {
        if (p->data == e)
        {
            if (p->lchild)
            {
                p = p->lchild;
                while (p->rchild) p = p->rchild;
                pre = p;
            }
            break;
        }
        else if (p->data < e)  pre = p, p = p->rchild;
        else p = p->lchild;
    }
    return pre->data;
}

int Get_Next(BSTree T, int e)
{
    BSTree next = T->rchild, p = T;
    while (p)
    {
        if (p->data == e)
        {
            if (p->rchild)
            {
                p = p->rchild;
                while (p->lchild) p = p->lchild;
                next = p;
            }
            break;
        }
        else if (p->data > e)  next = p, p = p->lchild;
        else p = p->rchild;
    }
    return next->data;
}

int main()
{
    BSTree T = NULL;
    int taller = FALSE, shoter = FALSE, n, op, x;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d %d", &op, &x);
        switch (op)
        {
        case 1:Insert(T, x, taller);break;
        case 2:Delete(T, x, shoter);break;
        case 3:printf("%d\n", Get_Rank(T, x));break;
        case 4:printf("%d\n", Get_Rank_Val(T, x));break;
        case 5:printf("%d\n", Get_Pre(T, x));break;
        case 6:printf("%d\n", Get_Next(T, x));break;
        }
    }
    return 0;
}

/////////////////////////  大佬写的  /////////////////////////////////////////////////////////
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100000 + 10;
template<class T> inline void read(T& x) {
    char c = 0;
    int f = x = 0;
    while (c < 48 || c > 57) {
        if (c == '-')
            f = 1;
        c = getchar();
    }
    while (c > 47 && c < 58) x = (x << 3) + (x << 1) + (c & 15), c = getchar();
    if (f) x = -x;
}
template<class T, class... Args> inline void read(T& x, Args&... args) {
    read(x), read(args...);
}
template<class T> inline void write(T x) {
    if (x < 0) {
        putchar(45);
        write(-x);
        return;
    }
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}
struct AVLnode;
typedef AVLnode* AVLtree;
struct AVLnode {
    int data, high;
    int freq, size;
    AVLtree ls, rs;
    AVLnode() : data(0), high(1), freq(1), size(1), ls(NULL), rs(NULL) {}
    AVLnode(int a) : data(a), high(1), freq(1), size(1), ls(NULL), rs(NULL) {}
};
inline int GetSize(AVLtree p) {
    if (p == NULL) return 0;
    return p->size;
}
inline int GetHigh(AVLtree p) {
    if (p == NULL) return 0;
    return p->high;
}
struct AVL {
    AVLtree root;
    inline void update(AVLtree& p) {
        p->size = GetSize(p->ls) + GetSize(p->rs) + p->freq;
        p->high = max(GetHigh(p->ls), GetHigh(p->rs)) + 1;
    }
    inline void LeftPlus(AVLtree& p) {
        AVLtree q;
        q = p->ls;
        p->ls = q->rs;
        q->rs = p;
        update(p);
        update(q);
        p = q;
    }
    inline void RightPlus(AVLtree& p) {
        AVLtree q;
        q = p->rs;
        p->rs = q->ls;
        q->ls = p;
        update(p);
        update(q);
        p = q;
    }
    inline void LeftRight(AVLtree& p) {
        RightPlus(p->ls);
        LeftPlus(p);
    }
    inline void RightLeft(AVLtree& p) {
        LeftPlus(p->rs);
        RightPlus(p);
    }
    inline void OutPut(AVLtree p) {
        if (p == NULL) return;
        OutPut(p->ls);
        for (int i = 1; i <= p->freq; ++i)
            write(p->data), putchar(32);
        OutPut(p->rs);
    }
    inline void output() {
        OutPut(root);
    }
    inline void Insert(AVLtree& p, int x) {
        if (p == NULL) {
            p = new AVLnode(x);
            return;
        }
        if (p->data == x) {
            ++(p->freq);
            update(p);
            return;
        }
        if (p->data > x) {
            Insert(p->ls, x), update(p);
            if (GetHigh(p->ls) - GetHigh(p->rs) == 2) {
                if (x < p->ls->data)
                    LeftPlus(p);
                else
                    LeftRight(p);
            }
        }
        else {
            Insert(p->rs, x), update(p);
            if (GetHigh(p->rs) - GetHigh(p->ls) == 2) {
                if (x > p->rs->data)
                    RightPlus(p);
                else
                    RightLeft(p);
            }
        }
        update(p);
    }
    inline void insert(int x) {
        Insert(root, x);
    }
    inline void Erase(AVLtree& p, int x) {
        if (p == NULL) return;
        if (p->data > x) {
            Erase(p->ls, x), update(p);
            if (GetHigh(p->rs) - GetHigh(p->ls) == 2) {
                if (GetHigh(p->rs->rs) >= GetHigh(p->rs->ls))
                    RightPlus(p);
                else
                    RightLeft(p);
            }
        }
        else if (p->data < x) {
            Erase(p->rs, x), update(p);
            if (GetHigh(p->ls) - GetHigh(p->rs) == 2) {
                if (GetHigh(p->ls->ls) >= GetHigh(p->ls->rs))
                    LeftPlus(p);
                else
                    LeftRight(p);
            }
        }
        else {
            if (p->freq > 1) {
                --(p->freq);
                update(p);
                return;
            }
            if (p->ls && p->rs) {
                AVLtree q = p->rs;
                while (q->ls) q = q->ls;
                p->freq = q->freq;
                p->data = q->data, q->freq = 1;
                Erase(p->rs, q->data);
                update(p);
                if (GetHigh(p->ls) - GetHigh(p->rs) == 2) {
                    if (GetHigh(p->ls->ls) >= GetHigh(p->ls->rs))
                        LeftPlus(p);
                    else
                        LeftRight(p);
                }
            }
            else {
                AVLtree q = p;
                if (p->ls) p = p->ls;
                else if (p->rs) p = p->rs;
                else p = NULL;
                delete q;
                q = NULL;
            }
        }
        if (p == NULL) return;
        update(p);
    }
    inline void erase(int x) {
        Erase(root, x);
    }
    inline int get_val(AVLtree p, int rank) {
        if (GetSize(p->ls) >= rank) return get_val(p->ls, rank);
        if (GetSize(p->ls) + p->freq >= rank) return p->data;
        return get_val(p->rs, rank - GetSize(p->ls) - p->freq);
    }
    inline int GetVal(int rank) {
        return get_val(root, rank);
    }
    inline int get_rank(AVLtree p, int val) {
        if (p->data == val) return GetSize(p->ls) + 1;
        if (p->data > val) return get_rank(p->ls, val);
        return get_rank(p->rs, val) + GetSize(p->ls) + p->freq;
    }
    inline int GetRank(int val) {
        return get_rank(root, val);
    }
    inline int GetPrev(int val) {
        AVLtree ans = new AVLnode(-1LL << 42), p = root;
        while (p) {
            if (p->data == val) {
                if (p->ls) {
                    p = p->ls;
                    while (p->rs)
                        p = p->rs;
                    ans = p;
                }
                break;
            }
            if (p->data < val && p->data > ans->data) ans = p;
            p = p->data < val ? p->rs : p->ls;
        }
        return ans->data;
    }
    inline int GetNext(int val) {
        AVLtree ans = new AVLnode(1LL << 42), p = root;
        while (p) {
            if (p->data == val) {
                if (p->rs) {
                    p = p->rs;
                    while (p->ls)
                        p = p->ls;
                    ans = p;
                }
                break;
            }
            if (p->data > val && p->data < ans->data) ans = p;
            p = p->data < val ? p->rs : p->ls;
        }
        return ans->data;
    }
};
int n, x, opt;
AVL a;
signed main() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(opt, x);
        switch (opt) {
        case 1: a.insert(x); break;
        case 2: a.erase(x); break;
        case 3: write(a.GetRank(x)), putchar(10); break;
        case 4: write(a.GetVal(x)), putchar(10); break;
        case 5: write(a.GetPrev(x)), putchar(10); break;
        case 6: write(a.GetNext(x)), putchar(10); break;
        }
    }
    return 0;
}