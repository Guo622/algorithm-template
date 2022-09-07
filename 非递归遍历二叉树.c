//先序遍历
void preorder(struct BITNode* t)
{
    struct BiTNode* St[MaxSize], * p;
    int top = 0;
    if (t != NULL)
    {
        St[top++] = t;
        while (top)
        {
            p = St[--top];
            printf("%c ", p->data);
            if (p->rchild != NULL)  //注意要先将右子树入栈
                St[top++] = p->rchild;
            if (p->lchild != NULL)
                St[top++] = p->lchild;
        }
        printf("\n");
    }
}

//中序遍历
void midorder(struct BiTNode* t)
{
    struct BiTNode* St[MaxSize], * p;
    int top = 0;
    do
    {
        while (t)
        {
            if (top == maxleng)
                exit(OVERFLOW);
            st[top++] = t;
            t = t->lchild;
        }
        if (top)
        {
            t = St[--top];
            printf("%c ", t->data);
            t = t->rchild;
        }
    } while (top || t);
}

//后序遍历
void postorder(struct BiTNode* t)
{
    struct BiTNode* st[MaxSize], * pre;
    int flag, top = 0;
    if (t != NULL)
    {
        do
        {
            while (t != NULL)
            {
                st[top++] = t;
                t = t->lchild;
            }
            pre = NULL;
            flag = 1;
            while (top && flag)
            {
                t = st[top - 1];
                if (t->rchild == pre)
                {
                    printf("%c ", t->data);
                    top--;
                    pre = t;
                }
                else
                {
                    t = t->rchild;
                    flag = 0;
                }
            }
        } while (top);
        printf("\n");
    }
}
