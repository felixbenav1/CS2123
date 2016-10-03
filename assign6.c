/********************** Assignment 6 **************************
Purpose:
	This program checks if a binary-search tree is a subset
	of another binary-search tree.
**************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct nodeT{
	int info;
	struct nodeT *left;
	struct nodeT *right;
} nodeT;

nodeT *insertNode(nodeT *p, int key);
int issubset(nodeT *tree1, nodeT *tree2);
int checkNum(nodeT *p, int key);
void printTree(nodeT *p, int n);
void freeAll(nodeT *p);

int main()
{
	nodeT *head1 = NULL;
	nodeT *head2 = NULL;
	int num, i;
	char c;
	printf("Enter the set of numbers for the first tree and press Enter:\n");
	while(c != '\n')
	{
		//get numbers for first tree
		i = scanf("%d%c", &num, &c);
		if(i != 2)
		{
			printf("Bad input.\n");
			exit(-1);
		}
		head1 = insertNode(head1, num);
	}
	printf("Enter the set of numbers for the second tree and press Enter:\n");
	c = ' ';
	while(c != '\n')
	{
		//get numbers for second tree
		scanf("%d%c", &num, &c);
		head2 = insertNode(head2, num);
	}
	i = issubset(head1, head2);
	if(i == 1)
		printf("First tree is a subset of second tree.\n");
	else
		printf("First tree is not a subset of second tree.\n");
	freeAll(head1);
	freeAll(head2);
	return 0;
}


nodeT *insertNode(nodeT *p, int key)
{
	if(p == NULL)
	{
		p = (nodeT *)malloc(sizeof(nodeT));
		if(p == NULL)
		{
			printf("Not enough memory.\n");
			exit(-1);
		}
		p->info = key;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	if(key < p->info)
		p->left = insertNode(p->left, key);
	else if(key > p->info)
		p->right = insertNode(p->right, key);
	return p;
}


int issubset(nodeT *tree1, nodeT *tree2)
{
	//check if done with first tree, base case
	if(tree1 == NULL)
		return 1;
	
	nodeT *p = tree2;
	int bool = 0;
	//traverse second tree and check if current number in first tree is found
	while(p != NULL)
	{
		if(tree1->info > p->info)
			p = p->right;
		else if(tree1->info < p->info)
			p = p->left;
		else if(tree1->info == p->info)
		{
			bool = 1;
			break;
		}
	}
	//return 1 if true for left and right subtrees of first tree
	return bool && issubset(tree1->left, tree2) && issubset(tree1->right, tree2);
}


void freeAll(nodeT *p)
{
	if(p == NULL)
		return;
	freeAll(p->left);
	freeAll(p->right);
	free(p);
}
