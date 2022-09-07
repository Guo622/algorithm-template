//https://www.cnblogs.com/skywang12345/p/3245399.html
#include<bits/stdc++.h>

#define RED 0         //红色结点
#define BLACK 1       //黑色结点
typedef int Type;

//红黑树的结点
typedef struct RBTNode
{
    unsigned char color;
    Type key;
    struct RBTNode* lchild;
    struct RBTNode* rchild;
    struct RBTNode* parent;
}Node, * RBTree;

RBTree Root = NULL;        //全局变量根结点

void L_Rotate(RBTree x)     //对x结点进行左旋
{
    RBTree y = x->rchild;
    x->rchild = y->lchild;
    if (y->lchild != NULL)  y->lchild->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)  Root = y;
    else
        if (x->parent->lchild == x)    x->parent->lchild = y;
        else    x->parent->rchild = y;
    y->lchild = x;
    x->parent = y;
}

void R_Rotate(RBTree x)     //对x结点进行右旋
{
    RBTree y = x->lchild;
    x->lchild = y->rchild;
    if (y->rchild != NULL)  y->rchild->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)  Root = y;
    else
        if (x->parent->lchild == x)    x->parent->lchild = y;
        else    x->parent->rchild = y;
    y->rchild = x;
    x->parent = y;
}

void Insert_Fixup(RBTree node);
void Insert(Type value)
{
    RBTree node = (RBTree)malloc(sizeof(Node));node->key = value;
    node->lchild = node->rchild = node->parent = NULL;node->color = RED;
    RBTree y = NULL, x = Root;
    while (x != NULL)
    {
        y = x;
        if (value < x->key)    x = x->lchild;
        else    x = x->rchild;
    }
    node->parent = y;
    if (y == NULL)  Root = node;
    else
        if (value < y->key)    y->lchild = node;
        else    y->rchild = node;
    Insert_Fixup(node);
}

void Insert_Fixup(RBTree node)
{
    RBTree par, gpa, uncle;
    while (node && (par = node->parent) && par->color == RED)
    {
        gpa = par->parent;
        if (par == gpa->lchild)
        {
            uncle = gpa->rchild;
            // Case 1条件：叔叔节点是红色
            if (uncle && uncle->color == RED)
            {
                uncle->color = BLACK;
                par->color = BLACK;
                gpa->color = RED;
                node = gpa;
            }
            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            else if (par->rchild == node)
            {
                L_Rotate(par);
                node = par;
            }
            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            else
            {
                par->color = BLACK;
                gpa->color = RED;
                R_Rotate(gpa);
                node = gpa->rchild;
            }
        }
        else
        {
            uncle = gpa->lchild;
            // Case 1条件：叔叔节点是红色
            if (uncle && uncle->color == RED)
            {
                uncle->color = BLACK;
                par->color = BLACK;
                gpa->color = RED;
                node = gpa;
            }
            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            else if (par->lchild == node)
            {
                R_Rotate(par);
                node = par;
            }
            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            else
            {
                par->color == BLACK;
                gpa->color = RED;
                L_Rotate(gpa);
                node = gpa->lchild;
            }
        }
    }
    Root->color = BLACK;
}

void Delete_Fixup(RBTree node, RBTree par);
void Delete(Type value)
{
    RBTree child, par, node = Root;
    int color;
    while (node && node->key != value)
    {
        if (value < node->key)     node = node->lchild;
        else    node = node->rchild;
    }
    if (node == NULL)   return;
    if (node->lchild != NULL && node->rchild != NULL)
    {
        RBTree rep = node->rchild;
        while (rep->lchild != NULL)     rep = rep->lchild;
        if (node->parent)
        {
            if (node->parent->lchild == node)
                node->parent->lchild = rep;
            else
                node->parent->rchild = rep;
        }
        else    Root = rep;
        child = rep->rchild;
        par = rep->parent;
        color = rep->color;
        if (par == node)   par = rep;
        else
        {
            if (child)      child->parent = par;
            par->lchild = child;
            rep->rchild = node->rchild;
            node->rchild->parent = rep;
        }
        rep->parent = node->parent;
        rep->color = node->color;
        rep->lchild = node->lchild;
        node->lchild->parent = rep;
        if (color == BLACK)    Delete_Fixup(child, par);
        free(node);
        return;
    }
    if (node->lchild != NULL)  child = node->lchild;
    else    child = node->rchild;
    par = node->parent;
    color = node->color;
    if (child)   child->parent = par;
    if (par)
        if (par->lchild == node)   par->lchild = child;
        else    par->rchild = child;
    else    Root = child;
    if (color == BLACK)    Delete_Fixup(child, par);
    free(node);
}

void Delete_Fixup(RBTree node, RBTree par)
{
    RBTree sib;
    while ((!node || node->color == BLACK) && node != Root)
    {
        if (par->lchild == node)
        {
            sib = par->rchild;
            // Case 1: x的兄弟w是红色的
            if (sib->color == RED)
            {
                sib->color = BLACK;
                par->color = RED;
                L_Rotate(par);
                sib = par->rchild;
            }
            // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
            else if ((!sib->lchild || sib->lchild->color == BLACK) &&
                (!sib->rchild || sib->rchild->color == BLACK))
            {
                sib->color = RED;
                node = par;
                par = node->parent;
            }
            // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
            else if (!sib->rchild || sib->rchild->color == BLACK)
            {
                sib->lchild->color = BLACK;
                sib->color = RED;
                R_Rotate(sib);
                sib = par->rchild;
            }
            else
            {
                sib->color = par->color;
                par->color = BLACK;
                sib->rchild->color = BLACK;
                L_Rotate(par);
                node = Root;
            }
        }
        else
        {
            sib = par->lchild;
            // Case 1: x的兄弟w是红色的
            if (sib->color == RED)
            {
                sib->color = BLACK;
                par->color = RED;
                R_Rotate(par);
                sib = par->lchild;
            }
            // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
            else if ((!sib->lchild || sib->lchild->color == BLACK) &&
                (!sib->rchild || sib->rchild->color == BLACK))
            {
                sib->color = RED;
                node = par;
                par = node->parent;
            }
            // Case 3: x的兄弟w是黑色的，并且w的右孩子是红色，左孩子为黑色。
            else if (!sib->lchild || sib->lchild->color == BLACK)
            {
                sib->rchild->color = BLACK;
                sib->color = RED;
                L_Rotate(sib);
                sib = par->lchild;
            }
            // Case 4: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
            {
                sib->color = par->color;
                par->color = BLACK;
                sib->lchild->color = BLACK;
                R_Rotate(par);
                node = Root;
            }
        }
    }
    if (node)    node->color = BLACK;
}

