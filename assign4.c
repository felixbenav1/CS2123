/********************* Assignment 4 **************************

*************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct nodeT{
	int key;
	int count;
	struct nodeT *left;
	struct nodeT *right;
} nodeT;

nodeT *insertNode(nodeT *p, int num);
void findKey(nodeT *p, int num);
int newCount(nodeT *p);
void printTree(nodeT *p);
void freeAll(nodeT *p);
void prettyPrintTree(nodeT *p, int n);

int main()
{
	nodeT *head = NULL;
	int num;
	char c;
	int i;
	printf("Enter the set of numbers for the tree and press Enter:\n");
	while(scanf("%d%c", &num, &c) == 2)
	{	
		head = insertNode(head, num);
		//printTree(head);
		//printf("\n");
		if(c == '\n')
			break;
	}
	//printTree(head);
	printf("\n");
	prettyPrintTree(head, 0);
	printf("\n");
	printf("Enter k and press Enter:\n");
	i = scanf("%d", &num);
	if(i != 1)
	{
		printf("Incorrect input.\n");
		freeAll(head);
		exit(-1);
	}
	findKey(head, num);
	freeAll(head);
	return 0;
}

nodeT *insertNode(nodeT *p, int num)
{
	nodeT *tmp;
	if(p == NULL)
	{
		tmp = (nodeT *)malloc(sizeof(nodeT));
		if(tmp == NULL)
		{
			printf("Not enough memory.\n");
			exit(-1);
		}
		tmp->key = num;
		tmp->count = 1;
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}
	if(p->key > num)
	{
		p->left = insertNode(p->left, num);
		p->count = 1 + newCount(p->left);
	}
	else if(p->key < num)
	{
		p->right = insertNode(p->right, num);
		p->count = 1 + newCount(p->left);
	}
	return p;
}

int newCount(nodeT *p)
{
	int i;
	if(p == NULL)
		return 0;
	return 1 + newCount(p->left) + newCount(p->right);
}

void printTree(nodeT *p)
{
	if(p == NULL)
		return;
	printTree(p->left);
	printf("%d %d\n", p->key, p->count);
	printTree(p->right);
}

void prettyPrintTree(nodeT *p, int n)
{
	if(p == NULL)
		return;
	int i;
	prettyPrintTree(p->right, n+1);
	for(i = 0; i < n; i++)
		printf("   ");
	printf("%d\n", p->key);
	prettyPrintTree(p->left, n+1);
}

void findKey(nodeT *p, int num)
{
	if(p == NULL)
	{
		printf("Number not found.\n");
		return;
	}
	if(num - p->count < 0)
		findKey(p->left, num);
	else if(num - p->count > 0)
		findKey(p->right, num - p->count);
	else
		printf("Result = %d\n", p->key);
}

void freeAll(nodeT *p)
{
	if(p == NULL)
		return;
	freeAll(p->left);
	freeAll(p->right);
	free(p);
}
