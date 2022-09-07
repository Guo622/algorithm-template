#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 已知中序和后序求先序
char inorder[9], postorder[9];
typedef struct treenode
{
    char data;
    struct treenode* left, * right;
} node;
void create(int x1, int y1, int x2, int y2, node*& p)
{
    if (x1 > y1 || x2 > y2)
        return;
    int i, j;
    for (i = x1, j = x2; i <= y1; i++, j++)
    {
        if (inorder[i] == postorder[y2])
            break;
    }
    p = (node*)malloc(sizeof(node));
    p->data = postorder[y2];
    p->left = p->right = NULL;
    create(x1, i - 1, x2, j - 1, p->left);
    create(i + 1, y1, j, y2 - 1, p->right);
    return;
}
void traverse(node* p)
{
    if (p == NULL)
        return;
    printf("%c", p->data);
    traverse(p->left);
    traverse(p->right);
    return;
}
int main()
{
    scanf("%s", inorder);
    scanf("%s", postorder);
    int len = strlen(inorder);
    node* root = NULL;
    create(0, len - 1, 0, len - 1, root);
    traverse(root);
    return 0;
}

//已知中序和先序求后序
char inorder[27], preorder[27];
typedef struct treenode
{
    char data;
    treenode* left, * right;
} node;
void create(int x1, int y1, int x2, int y2, node*& p)
{
    if (x1 > y1 || x2 > y2)
        return;
    int i, j;
    for (i = x1, j = x2; i <= y1; i++, j++)
    {
        if (inorder[j] == preorder[x1])
            break;
    }
    p = (node*)malloc(sizeof(node));
    p->data = preorder[x1];
    p->left = p->right = NULL;
    create(x1 + 1, i, x2, j - 1, p->left);
    create(i + 1, y1, j + 1, y2, p->right);
    return;
}
void traverse(node* p)
{
    if (p == NULL)
        return;
    traverse(p->left);
    traverse(p->right);
    printf("%c", p->data);
    return;
}
int main()
{
    scanf("%s", inorder);
    scanf("%s", preorder);
    int len = strlen(inorder);
    node* root = NULL;
    create(0, len - 1, 0, len - 1, root);
    traverse(root);
    return 0;
}