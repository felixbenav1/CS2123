/************************* Assignment 5 ***********************
Purpose:
	This function inserts numbers given by the user into a 
	binary search tree and prints the tree on its side.
**************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct nodeT{
	int info;
	struct nodeT *left;
	struct nodeT *right;
} nodeT;

nodeT *insertNode(nodeT *p, int key);
void printTreeOnSide(nodeT *p, int n);
void freeAll(nodeT *p);

int main()
{
	int num;
	char c;
	nodeT *root = NULL;
	printf("Enter the numbers for the binary search tree and press Enter:\n");
	while(c != '\n')
	{
		//insert each number one by one
		scanf("%d%c", &num, &c);
		root = insertNode(root, num);
	}
	printf("Result:\n");
	printTreeOnSide(root, 0);
	freeAll(root);
	return 0;
}

/************************* insertNode ***************************
Purpose:
	This function inserts a node into a binary search tree.
****************************************************************/
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

/************************* printTreeOnSide ************************
Purpose:
	This function prints a tree out o its side.
******************************************************************/
void printTreeOnSide(nodeT *p, int n)
{
	if(p == NULL)
		return;
	printTreeOnSide(p->right, n + 1);   //go to rightmost node first
	int i;
	for(i = 0; i < n; i++)
	{
		//print 4*n spaces for a node at depth n
		printf("    ");	
	}
	printf("%d\n", p->info);
	printTreeOnSide(p->left, n + 1);    //go to leftmost node last
}

/************************* freeAll ********************************
Purpose:
	This function frees all allocated nodes in a binary search
	tree.
******************************************************************/
void freeAll(nodeT *p)
{
	if(p == NULL)
		return;
	freeAll(p->left);
	freeAll(p->right);
	free(p);
}
