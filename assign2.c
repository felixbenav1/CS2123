/**************** Assignment 2 *********************

***************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int info;
	struct node *next;
} node;

typedef struct cnode{
	int info;
	struct cnode *next;
	struct cnode *previous;
} cnode;

node *CopytoSinglyLinked(cnode *head);
node *Previous(node *head, node *current);
void PrintReverse(node *head);
node *RemoveDuplicates(node *head);
cnode *CreateDoubly();
void printSinglyList(node *head);
void printDoublyList(cnode *chead);

int main()
{
	node *p;
	cnode *chead;
	chead = CreateDoubly();
	p = CopytoSinglyLinked(chead);
	PrintReverse(p);
	p = RemoveDuplicates(p);
	free(chead);
	free(p);
	return 0;
}

/**************** CopytoSinglyLinked *****************

******************************************************/
node *CopytoSinglyLinked(cnode *chead)
{
	printf("Copy to singly linked list:\n");
	cnode *cp;
	node *p;
	node *head;
	if(chead == NULL)
		return NULL;
	head = (node *) malloc(sizeof(node));
	head->info = chead->info;
	head->next = NULL;
	for(cp = chead->next, p = head; cp != NULL; cp = cp->next, p = p->next)
	{
		p->next = (node *)malloc(sizeof(node));
		p->next->info = cp->info;
		p->next->next = NULL;
	}
	printSinglyList(head);
	return head;
}

/******************* Previous *************************

******************************************************/
node *Previous(node *head, node *current)
{
	node *p;
	if(head == current)
		return NULL;
	for(p = head; p != NULL; p = p->next)
	{
		if(p->next == current)
			return p;
	}
	return NULL;
}

/****************** PrintReverse **********************

******************************************************/
void PrintReverse(node *head)
{
	printf("Print Reverse:\n");
	node *p;
	node *p2;
	int i = 0;
	int j;
	if(head == NULL)
		return;
	for(p = head; p->next != NULL; p = p->next)
	{
		i++;
	}
	printf("%d ", p->info);
	for(j = 0; j < i; j++)
	{
		p2 = Previous(head, p);
		printf("%d ", p2->info);
		p = p2;
	}
	printf("\n");
	return;
}

/****************** RemoveDuplicates ******************

*******************************************************/
node *RemoveDuplicates(node *head)
{
	printf("Remove Duplicates:\n");
	node *p;
	node *p2;
	node *p3;
	node *p4;
	for(p = head; p != NULL; p = p->next)
	{
		for(p2 = p->next; p2 != NULL; p2 = p3->next)
		{
			if(p2->info == p->info)
			{
				p4 = p2;
				p3 = Previous(head, p2);
				p3->next = p2->next;
				free(p4);
			}
			else{
				p3 = p2;
			}
		}
	}
	printSinglyList(head);
	return head;
}

/********************* CreateDoubly ***********************

**********************************************************/
cnode *CreateDoubly()
{
	printf("Create Doubly List:\n");
	int i;
	cnode *chead = NULL;
	cnode *cp;
	chead = (cnode *)malloc(sizeof(cnode));
	if(chead == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	chead->info = 2;
	chead->previous = NULL;
	chead->next = NULL;
	for(i = 1, cp = chead; i < 5; i++, cp = cp->next)
	{
		cp->next = (cnode *)malloc(sizeof(cnode));
		if(cp->next == NULL)
		{
			printf("No memory available.\n");
			break;
		}
		cp->next->info = i;
		cp->next->previous = cp;
		cp->next->next = NULL;
	}
	printDoublyList(chead);
	return chead;
}

/******************* printSinglyList ***********************

***********************************************************/
void printSinglyList(node *head)
{
	node *p;
	for(p = head; p != NULL; p = p->next)
	{
		printf("%d ", p->info);
	}
	printf("\n");
}

/************************* printDoublyList **********************

****************************************************************/
void printDoublyList(cnode *chead)
{
	cnode *cp;
	for(cp = chead; cp != NULL; cp = cp->next)
	{
		printf("%d ", cp->info);
	}
	printf("\n");
}
