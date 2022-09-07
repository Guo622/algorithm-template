#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Node
{
    int data;
    int freq, size, height;
    Node* left, * right;
    Node() :data(0), height(1), freq(1), size(1), left(NULL), right(NULL) {}
    Node(int x) :data(x), height(1), freq(1), size(1), left(NULL), right(NULL) {}
};
using AVLtree = Node*;

inline int getSize(AVLtree p) { return p == NULL ? 0 : p->size; }

inline int getHeight(AVLtree p) { return p == NULL ? 0 : p->height; }

inline void update(AVLtree& p) {
    if (p == NULL) return;
    p->size = getSize(p->left) + getSize(p->right) + p->freq;
    p->height = max(getHeight(p->left), getHeight(p->right)) + 1;
}

inline void leftPlus(AVLtree& p) {
    AVLtree q = p->left;
    p->left = q->right;
    q->right = p;
    update(p); update(q);
    p = q;
}

inline void rightPlus(AVLtree& p) {
    AVLtree q = p->right;
    p->right = q->left;
    q->left = p;
    update(p); update(q);
    p = q;
}

inline void leftRight(AVLtree& p) {
    rightPlus(p->left);
    leftPlus(p);
}

inline void rightLeft(AVLtree& p) {
    leftPlus(p->right);
    rightPlus(p);
}

void insert(AVLtree& p, int x) {
    if (p == NULL) { p = new Node(x); return; }
    if (p->data == x) { ++(p->freq); ++(p->size);  return; }
    if (p->data > x) {
        insert(p->left, x); update(p);
        if (getHeight(p->left) - getHeight(p->right) == 2) {
            if (x < p->left->data) leftPlus(p);
            else leftRight(p);
        }
    }
    else {
        insert(p->right, x); update(p);
        if (getHeight(p->right) - getHeight(p->left) == 2) {
            if (x > p->right->data) rightPlus(p);
            else rightLeft(p);
        }
    }
}

void erase(AVLtree& p, int x) {
    if (p == NULL) return;
    if (p->data == x) {
        if (p->freq > 1) { --(p->freq);--(p->size); return; }
        if (p->left && p->right) {
            AVLtree q = p->right;
            while (q->left) q = q->left;
            p->freq = q->freq; p->data = q->data;
            q->freq = 1;
            erase(p->right, q->data); update(p);
            if (getHeight(p->left) - getHeight(p->right) == 2) {
                if (getHeight(p->left->left) >= getHeight(p->left->right))
                    leftPlus(p);
                else
                    leftRight(p);
            }
        }
        else {
            AVLtree q = p;
            if (p->left) p = p->left;
            else if (p->right) p = p->right;
            else p = NULL;
            delete q; q = NULL;
        }
    }
    else if (p->data > x) {
        erase(p->left, x); update(p);
        if (getHeight(p->right) - getHeight(p->left) == 2) {
            if (getHeight(p->right->right) >= getHeight(p->right->left))
                rightPlus(p);
            else
                rightLeft(p);
        }
    }
    else {
        erase(p->right, x); update(p);
        if (getHeight(p->left) - getHeight(p->right) == 2) {
            if (getHeight(p->left->left) >= getHeight(p->left->right))
                leftPlus(p);
            else
                leftRight(p);
        }
    }
}

inline int getVal(AVLtree p, int rank) {
    if (getSize(p->left) >= rank) return getVal(p->left, rank);
    if (getSize(p->left) + p->freq >= rank) return p->data;
    return getVal(p->right, rank - getSize(p->left) - p->freq);
}

inline int getRank(AVLtree p, int x) {
    if (p->data == x) return getSize(p->left) + 1;
    if (p->data > x) return getRank(p->left, x);
    return getRank(p->right, x) + getSize(p->left) + p->freq;
}

int getPrev(AVLtree root, int x) {
    AVLtree q = new Node(-0x7fffffff), temp = q, p = root;
    while (p) {
        if (p->data == x) {
            if (p->left) {
                p = p->left;
                while (p->right) p = p->right;
                q = p;
            }
            break;
        }
        if (p->data<x && p->data>q->data) q = p;
        p = p->data < x ? p->right : p->left;
    }
    int ans = q->data; delete temp;
    return ans;
}

int getNext(AVLtree root, int x) {
    AVLtree q = new Node(0x7fffffff), temp = q, p = root;
    while (p) {
        if (p->data == x) {
            if (p->right) {
                p = p->right;
                while (p->left) p = p->left;
                q = p;
            }
            break;
        }
        if (p->data > x && p->data < q->data) q = p;
        p = p->data < x ? p->right : p->left;
    }
    int ans = q->data; delete temp;
    return ans;
}
int main() {
    AVLtree root = NULL;
    int x, opt, n;
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &opt, &x);
        switch (opt) {
        case 1:insert(root, x);break;
        case 2:erase(root, x);break;
        case 3:printf("%d\n", getRank(root, x));break;
        case 4:printf("%d\n", getVal(root, x));break;
        case 5:printf("%d\n", getPrev(root, x));break;
        case 6:printf("%d\n", getNext(root, x));break;
        }
    }
    return 0;
}