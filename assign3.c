/******************** Assignment 3 ***************************

*************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct cnode{
	int info;
	struct cnode *previous;
	struct cnode *next;
} cnode;

cnode *createDoubly(cnode *chead, int num, int *bool);
cnode *doublytoTree(cnode *cp, int count, int mid, int bool);
void printDoubly(cnode *cp);
void printTree(cnode *cp, int count);
void printTreePreOrder(cnode *cp);
void freeAll(cnode *chead);

int main()
{
	cnode *chead = NULL;
	int count;
	int num;
	char enter;
	int bool = 0;
	int i;
	printf("Enter numbers for doubly linked list in sorted order:\n");		//prompt user to enter numbers for doubly linked list
	while(enter != '\n')												//check if the newline was hit
	{
		scanf("%d%c", &num, &enter);
		chead = createDoubly(chead, num, &bool);
		if(bool == 0){													//check if numbers were entered in sorted order
			printf("Numbers not entered in sorted order.\n");			
			freeAll(chead);
			return 0;
		}
	}
	printf("Doubly Linked List Contents:\n");					//show user the doubly linked list
	printDoubly(chead);						
	printf("\n");
	count = countNodes(chead);								//count number of nodes in doubly linked list	
	chead = doublytoTree(chead, count, count/2, 1);			//convert doubly linked list to binary search tree
	printf("Binary Search Tree Contents\n");
	printTreePreOrder(chead);
	printf("\n\n");
	printTree(chead, 0);								//print tree in tree-like structure
	//printf("\n");
	freeAll(chead);									//free doubly linked list/tree to prevent memory leaks
	return 0;
}

/***************** createDoubly ******************************

**************************************************************/
cnode *createDoubly(cnode *chead, int num, int *bool)
{
	int i;
	cnode *chead2;
	if(chead == NULL)
	{
		chead2 = (cnode *)malloc(sizeof(cnode));			//list is empty, start new list
		if(chead2 == NULL)
		{
			printf("Not enough memory.\n");
			return NULL;
		}
		chead2->info = num;;
		chead2->previous = NULL;
		chead2->next = NULL;
		*bool = 1;				//number is entered correctly
		return chead2;
	}
	cnode *cp = chead;						//list is not empty
	while(cp->next != NULL)						//traverse list until last node
	{
		cp = cp->next;
	}
	if(cp->info > num)
	{
		*bool = 0;					//if last node is greater than number entered, then user did not enter numbers sorted
		return chead;
	}
	cp->next = (cnode *)malloc(sizeof(cnode));		//number is entered correctly, make new node
	if(cp == NULL)
	{
		printf("Not enough memory.\n");
		return chead;
	}
	cp->next->info = num;
	cp->next->previous = cp;
	cp->next->next = NULL;
	*bool = 1;					// number is entered correctly
	return chead;	
}

/***************** countNodes ******************************

***********************************************************/
int countNodes(cnode *chead)
{
	int sum = 0;		//count of number of nodes in doubly linked list
	cnode *cp;
	for(cp = chead; cp != NULL; cp = cp->next)
	{
		sum++;			//current node is not NULL, add one to count
	}
	return sum;
}

/*************************** doublytoTree ***************************

********************************************************************/
cnode *doublytoTree(cnode *cp, int total, int mid, int bool)
{
	int i;
	if(mid == total || cp == NULL)
	{
		return NULL;			//all nodes have been processed, base case
	}
	if(cp->previous == NULL && cp->next == NULL)
		return cp;				//if previous and next node is NULL then that subtree is complete
	if(bool == 0)
	{
		for(i = 0; i < mid; i++)
		{
			cp = cp->previous;		//traverse list backwards to get to middle node of left subtree
			if(cp->previous == NULL)
				break;
		}
	}
	else{
		for(i = 0; i < mid; i++)
		{
			cp = cp->next;			//traverse list to get middle node of right subtree
			if(cp->next == NULL)
				break;
		}
	}
	if(cp->next == NULL && cp->previous != NULL)
		cp->previous->next = NULL;					//check if next node is NULL to avoid segmentation fault
	else if(cp->previous == NULL && cp->next != NULL)
		cp->next->previous = NULL;					//check if preious node is NULL to avoid segmentation fault
	else{
		cp->previous->next = NULL;				//neither previous or next were NULL
		cp->next->previous = NULL;			//so convert them to NULL to show them as children of current node
	}
	cp->previous = doublytoTree(cp->previous, total/2, mid/2, 0);		//recursive call for left subtree
	cp->next = doublytoTree(cp->next, total/2, mid/2, 1);			//recursive call for right subtree
	return cp; 
}

/*********************** printDoubly ********************************

********************************************************************/
void printDoubly(cnode *cp)
{
	while(cp->next != NULL)
	{
		printf("%d ", cp->info);		//print list forward
		cp = cp->next;
	}
	printf("%d\n", cp->info);
	while(cp->previous != NULL)
	{
		printf("%d ", cp->info);		//print list backward to check previous pointers
		cp = cp->previous;
	}
	printf("%d\n", cp->info);
}

void printTree(cnode *cp, int count)
{
	int i;
	if(cp == NULL)
		return;
	printTree(cp->next, count+1);
	for(i = 0; i < count; i++)
	{
		printf("  ");			//print spaces to print numbers in tree-like fashion
	}
	printf("%d\n", cp->info);
	printTree(cp->previous, count + 1);
}

void printTreePreOrder(cnode *cp)
{
	if(cp == NULL)
		return;
	printTreePreOrder(cp->previous);
	printf("%d ", cp->info);
	printTreePreOrder(cp->next);
}

/*********************** freeAll *********************************

*****************************************************************/
void freeAll(cnode *chead)
{
	cnode *cp;
	while(chead != NULL)
	{
		cp = chead;
		chead = chead->next;		//traverse list, go to next node
		free(cp);				//free current node
	}
}
