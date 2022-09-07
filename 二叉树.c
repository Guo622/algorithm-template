#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef struct tree_node
{
	struct tree_node* left;
	struct tree_node* right;
	int value;
}treenode;
treenode* root = NULL;
void insert(int value)
{
	treenode* current;
	treenode** link = &root;
	while ((current = *link) != NULL)
	{
		assert(current->value);
		if (value < current->value)
			link = &current->left;
		else
			link = &current->right;
	}
	current = (treenode*)malloc(sizeof(treenode));
	assert(current);
	current->value = value;
	current->left = current->right = NULL;
	*link = current;
}
treenode* find(int value)
{
	treenode* current = root;
    while (current != NULL && current->value != value)
	{
		if (value < current->value)
			current = current->left;
		else
			current = current->right;
	}
	return current;
}
void traverse(treenode* current)
{
	if (current)
	{
		printf("%d ", current->value);
		traverse(current->left);
		traverse(current->right);
	}
}
void destroy(treenode* rootp)
{
	while (rootp->left)
	{
		destroy(rootp->left);
		break;
	}
	while (rootp->right)
	{
		destroy(rootp->right);
		break;
	}
	free(rootp);
}
int main()
{
	int test[] = { 20,12,5,9,16,17,25,28,26,29 };
	for (int i = 0; i < 10; i++)
		insert(test[i]);
	traverse(root);
	destroy(root);
	return 0;
}
