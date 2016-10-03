/********************** Bonus Assignment **********************
Bonus Assignment by Felix Benavides
Purpose:
	The purpose of this program is to construct a binary
	search tree and randomly select a number from it 1000
	times and print out each element's probability. Each
	element should have around the same probability.
**************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct nodeT{
	int key;
	int count;
	double p;
	struct nodeT *left;
	struct nodeT *right;
} nodeT;


nodeT *insertNode(nodeT *p, int num);
int newCount(nodeT *p);
void printTree(nodeT *p);
void findKey(nodeT *p, int num);
void printProbability(nodeT *p);
void freeAll(nodeT *p);

int main()
{
	int i, num, count;
	char c = ' ';
	nodeT *root = NULL;
	
	printf("Enter the set of numbers for the tree:\n");
	while(c != '\n')
	{
		i = scanf("%d%c", &num, &c);
		if(i != 2)
		{
			printf("Incorrect input.\n");
			freeAll(root);
			return 0;
		}
		root = insertNode(root, num);
	}
	
	//count number of elements in tree
	count = newCount(root);
	//printf("%d\n", count);
	//printTree(root);
	
	srand(time(NULL));
	for(i = 0; i < 1000; i++)
	{
		//do 1000 random selections
		num = rand() % count;
		num++;				//add 1 to exclude 0
		findKey(root, num);		//find kth smallest number
	}
	
	printf("Probabilities after 1000 random selections are:\n");
	printProbability(root);
	
	freeAll(root);
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
		tmp->p = 0;
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}
	if(p->key >= num)
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


void findKey(nodeT *p, int num)
{
	if(p == NULL)
	{
		return;
	}
	if(num - p->count < 0)
		findKey(p->left, num);		//number in left subtree
	else if(num - p->count > 0)
		findKey(p->right, num - p->count);		//number in right subtree
	else
		p->p = p->p + 1;		//found kth smallest element
}


void printProbability(nodeT *p)
{
	if(p == NULL)
		return;
	printf("p(%d) = %8.6lf\n", p->key, p->p/1000);
	printProbability(p->left);	
	printProbability(p->right);
}


void freeAll(nodeT *p)
{
	if(p == NULL)
		return;
	freeAll(p->left);
	freeAll(p->right);
	free(p);
}
