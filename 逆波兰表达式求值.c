#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	struct node* former;
}node;
typedef struct stack
{
	node* top;
}stack;
reset(stack* stk)
{
	node* cur;
	cur = (node*)malloc(sizeof(node));
	cur->former = NULL;
	stk->top = cur;
}
push(int x, stack* stk)
{
	node* cur;
	stk->top->data = x;
	cur = (node*)malloc(sizeof(node));
	cur->former = stk->top;
	stk->top = cur;
}
int pop(stack* stk)
{
	node* cur;
	int x;
	cur = stk->top;
	stk->top = stk->top->former;
	x =stk->top->data;
	free(cur);
	return x;
}
int main(void)
{
	char c_former=' ', c_current=' ';
	int n = 0, right;
	stack stk;
 	reset(&stk);
	do
	{
		c_former = c_current;
		if (c_former == '\n')	break;
		c_current = getchar();
		switch (c_current)
		{
			case'0':case'1':case'2':case'3':case'4':
			case'5':case'6':case'7':case'8':case'9':
				n = n * 10 + c_current - '0';
				break;
			case' ':
			case'\n':
				switch (c_former)
				{
					case'+':
						right = pop(&stk);
						push(pop(&stk) + right,&stk);
						break;
					case'-':
						right = pop(&stk);
						push(pop(&stk) - right, &stk);
						break;
					case'*':
						right = pop(&stk);
						push(pop(&stk) * right, &stk);
						break;
					case'/':
						right = pop(&stk);
						push(pop(&stk) / right, &stk);
						break;
					case' ':break;
					default:
						push(n, &stk);
						n = 0;
						break;
				}
			case'+':case'-':case'*':case'/':
				break;
			default:break;
		}
	} while (1);
	printf("%d", pop(&stk));
	return 0;
}
