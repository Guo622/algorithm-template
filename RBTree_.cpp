#include<iostream>
#include<cstdio>
#include<vector>
using std::vector;
enum { RED, BLACK };

struct Node;
using RBTree = Node*;

struct Node {
    RBTree left, right, parent;
    int data, color, size, freq;
    Node() : data(0), size(1), freq(1) {}
    Node(int x) : data(x), size(1), freq(1) {}
};

struct Tree {
    RBTree root, nil;
    Tree() :root(new Node()), nil(root) {
        root->parent = nil;nil->color = BLACK;nil->size = nil->freq = 0;
        nil->parent = nil->left = nil->right = NULL;
    }
    void update(RBTree p);
    void leftRotate(RBTree x);
    void rightRotate(RBTree x);
    void insertFixup(RBTree z);
    void insert(int x);
    void transplant(RBTree u, RBTree v);
    void eraseFixup(RBTree x);
    void erase(int x);
    int getPrev(int x);
    int getNext(int x);
    int select(int rank);
    int getRank(int x);
    void destroy(RBTree t) {
        if (t == nil)  return;
        destroy(t->left);
        destroy(t->right);
        delete t;
    }
    ~Tree() {
        if (root == nil) delete nil;
        else { destroy(root);delete nil; }
    }
};

void Tree::update(RBTree p) {
    if (p == nil) return;
    p->size = p->left->size + p->right->size + p->freq;
}

void Tree::leftRotate(RBTree x) {
    RBTree y = x->right;
    x->right = y->left;
    if (y->left != nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x; x->parent = y;
    update(x); update(y);
}

void Tree::rightRotate(RBTree x) {
    RBTree y = x->left;
    x->left = y->right;
    if (y->right != nil) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x; x->parent = y;
    update(x); update(y);
}


void Tree::insert(int d) {
    RBTree y = nil, x = root;
    while (x != nil) {
        x->size++;
        y = x;
        if (d < x->data) x = x->left;
        else if (d > x->data)x = x->right;
        else { x->freq++;  return; }
    }
    RBTree z = new Node(d);
    z->parent = y;
    if (y == nil) root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;
    z->left = z->right = nil;
    z->color = RED;
    insertFixup(z);
}

void Tree::insertFixup(RBTree z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTree y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->right) {
                z = z->parent;
                leftRotate(z);
            }
            else {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else {
            RBTree y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->left) {
                z = z->parent;
                rightRotate(z);
            }
            else {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Tree::transplant(RBTree u, RBTree v) {
    if (u->parent == nil) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
    update(u->parent);
}

void Tree::erase(int d) {
    RBTree z = root;
    while (z != nil) {
        z->size--;
        if (z->data == d) {
            if (z->freq > 1) { z->freq--; return; }
            else break;
        }
        else if (z->data < d) z = z->right;
        else z = z->left;
    }
    RBTree y = z, x;
    int y_original_color = y->color;
    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        RBTree p = z->right;
        vector<RBTree> v;
        while (p->left != nil) {
            v.push_back(p);
            p = p->left;
        }
        y = p;
        for (RBTree i : v) i->size -= y->freq;
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            transplant(y, x);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        update(y); update(y->parent);
    }
    delete z;
    if (y_original_color == BLACK)
        eraseFixup(x);
}

void Tree::eraseFixup(RBTree x) {
    RBTree w;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED; x = x->parent;
            }
            else if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                rightRotate(w);
                w = x->parent->right;
            }
            else {
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;x = x->parent;
            }
            else if (w->left->color == BLACK) {
                w->right->color = BLACK;
                w->color = RED;
                leftRotate(w);
                w = x->parent->left;
            }
            else {
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

int Tree::getPrev(int x) {
    RBTree q = new Node(-0x7fffffff), temp = q, p = root;
    while (p != nil) {
        if (p->data == x) {
            if (p->left != nil) {
                p = p->left;
                while (p->right != nil) p = p->right;
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

int Tree::getNext(int x) {
    RBTree q = new Node(0x7fffffff), temp = q, p = root;
    while (p != nil) {
        if (p->data == x) {
            if (p->right != nil) {
                p = p->right;
                while (p->left != nil) p = p->left;
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


int Tree::select(int rank) {
    RBTree x = root;
    int r = x->left->size;
    while (r >= rank) {
        x = x->left;
        r = x->left->size;
    }
    while (r + x->freq < rank) {
        rank = rank - r - x->freq;
        x = x->right;
        r = x->left->size;  //774
        while (r >= rank) {
            x = x->left;
            r = x->left->size;
        }
    }
    return x->data;
}

int Tree::getRank(int x) {
    int r = 1;
    RBTree p = root;
    while (p != nil) {
        if (x > p->data) {
            r += (p->left->size + p->freq);
            p = p->right;
        }
        else if (x == p->data) {
            r += p->left->size;
            break;
        }
        else p = p->left;
    }
    return r;
}

int main() {
    Tree T;
    int x, opt, n;
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &opt, &x);
        switch (opt) {
        case 1:T.insert(x);break;
        case 2:T.erase(x);break;
        case 3:printf("%d\n", T.getRank(x));break;
        case 4:printf("%d\n", T.select(x));break;
        case 5:printf("%d\n", T.getPrev(x));break;
        case 6:printf("%d\n", T.getNext(x));break;
        }
    }
    return 0;
}