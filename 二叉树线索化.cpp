#include <stdlib.h>
#include <stdio.h>

typedef char TElemType;
typedef enum { Link, Thread } PointerTag;
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode* lchild, * rchild;
    PointerTag LTag, RTag;
} BiThrNode, * BiThrTree;
BiThrNode* pre = NULL;  //全局变量pre
void InThreading(BiThrTree p);
void InOrderTraverse_Thr(BiThrTree T)
{
    //T指向头结点，头结点lchild指向根结点
    //中序遍历二叉线索树
    BiThrNode* p = T->lchild;
    while (p != T)
    {
        while (p->LTag == Link)  p = p->lchild;
        printf("%c ", p->data);
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            printf("%c ", p->data);
        }
        p = p->rchild;
    }
    return;
}

void InOrderThreading(BiThrTree& Thrt, BiThrTree T)
{
    if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
        return;
    Thrt->LTag = Link;    Thrt->RTag = Thread;
    Thrt->rchild = Thrt;
    if (!T)    Thrt->lchild = Thrt;
    else
    {
        Thrt->lchild = T;
        pre = Thrt;
        InThreading(T);
        pre->rchild = Thrt;
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
    return;
}
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild); //左子树线索化
        if (!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = pre;
        }                         //前驱线索
        if (!pre->rchild)
        {
            pre->RTag = Thread;
            pre->rchild = p;
        }                         //后驱线索
        pre = p;
        InThreading(p->rchild);   //右子树线索化
    }
}
int main()
{
    BiThrTree Thrt, T;
    Thrt = T = NULL;
    BiThrTree leaves[6], roots[5];       //"a+b*c-d-e/f"
    char c = 'a';
    for (int i = 0; i < 6; i++)
    {
        leaves[i] = (BiThrTree)malloc(sizeof(BiThrNode));
        leaves[i]->lchild = leaves[i]->rchild = NULL;
        leaves[i]->LTag = leaves[i]->RTag = Thread;
        leaves[i]->data = c + i;
    }
    for (int i = 0; i < 5; i++)
    {
        roots[i] = (BiThrTree)malloc(sizeof(BiThrNode));
        roots[i]->LTag = roots[i]->RTag = Link;
    }
    roots[0]->data = '-', roots[0]->lchild = leaves[2], roots[0]->rchild = leaves[3];
    roots[1]->data = '*', roots[1]->lchild = leaves[1], roots[1]->rchild = roots[0];
    roots[2]->data = '+', roots[2]->lchild = leaves[0], roots[2]->rchild = roots[1];
    roots[3]->data = '/', roots[3]->lchild = leaves[4], roots[3]->rchild = leaves[5];
    roots[4]->data = '-', roots[4]->lchild = roots[2], roots[4]->rchild = roots[3];
    T = roots[4];
    InOrderThreading(Thrt, T);
    InOrderTraverse_Thr(Thrt);
    return 0;
}