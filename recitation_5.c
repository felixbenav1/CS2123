/******************** Recitation 5 **********************

********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
	double x;
	double y;
	struct node *next;
} node;

node *insertNearestNeighbor(node *head, double x, double y);
node *insertSmallestIncrease(node *head, double x, double y);
double findLength(node *head);
void printTour(node *head, double length, FILE *file);
void freeAll(node *head);

int main(int argc, char *argv[])
{
	FILE *inputf;
	FILE *nearestf;
	FILE *smallestf;
	int i, n;
	double x, y, nearestlength, smallestlength;
	char szInputBuffer[120];
	node *head = NULL;
	node *head2 = NULL;
	
	if(argc != 4)
	{
		printf("Incorrect input.\n");
		exit(-1);
	}
	inputf = fopen(argv[1], "r");
	if(inputf == NULL)
	{
		perror(argv[1]);
		exit(-1);
	}
	nearestf = fopen(argv[2], "w");
	if(nearestf == NULL)
	{
		perror(argv[2]);
		exit(-1);
	}
	smallestf = fopen(argv[3], "w");
	if(smallestf == NULL)
	{
		perror(argv[3]);
		exit(-1);
	}
	fscanf(inputf, "%d", &n);		//check n?
	for(i = 1; i <= n; i++)
	{
		if(fgets(szInputBuffer, 120, inputf) != NULL)
		{
			sscanf(szInputBuffer, "%lf %lf", &x, &y);
			head = insertNearestNeighbor(head, x, y);
			head2 = insertSmallestIncrease(head2, x, y);
		}
		/*else{
			printf("Not enough points.\n");
		}*/
	}
	nearestlength = findLength(head);
	smallestlength = findLength(head2);
	printTour(head, nearestlength, nearestf);
	printTour(head2, smallestlength, smallestf);
	freeAll(head);
	freeAll(head2);
	return 0;
}

node *insertNearestNeighbor(node *head, double x, double y)
{
	node *p;
	if(head == NULL)
	{
		p = (node *)malloc(sizeof(node));
		p->x = x;
		p->y = y;
		p->next = p;
		return p;
	}
	/*if(head->next == head)
	{
		p = (node *)malloc(sizeof(node));
		p->x = x;
		p->y = y;
		head->next = p;
		p->next = head;
		return p;
	}*/
	double min, num;
	node *p2;
	p2 = head;
	min = sqrt(pow(x - head->x, 2) + pow(y - head->y, 2));
	for(p = head->next; p != head; p = p->next)
	{
		num = sqrt(pow(x - p->x, 2) + pow(y - p->y, 2));
		if(num < min)
		{
			min = num;
			p2 = p;
		}
	}
	if(p2 == head)
	{
		p = (node *)malloc(sizeof(node));
		p->x = x;
		p->y = y;
		p->next = head->next;
		head->next = p;
		return p;
	}
	else{
		p = (node *)malloc(sizeof(node));
		p->x = x;
		p->y = y;
		p->next = p2->next;
		p2->next = p;
		return head;
	}
}

node *insertSmallestIncrease(node *head, double x, double y)
{
	node *p;
	if(head == NULL)
	{
		p = (node *)malloc(sizeof(node));
		p->x = x;
		p->y = y;
		p->next = p;
		return p;
	}
	if(head->next == head)
	{
		p = (node *)malloc(sizeof(node));
		p->x = x;
		p->y = y;
		head->next = p;
		p->next = head;
		return p;
	}
	double min, num;
	node *p2;
	p2 = head;
	min = sqrt(pow(x - head->x, 2) + pow(y - head->y, 2)) + sqrt(pow(head->next->x - x, 2) + pow(head->next->y - y, 2));
	for(p = head->next; p != head; p = p->next)
	{
		num = sqrt(pow(x - p->x, 2) + pow(y - p->y, 2)) + sqrt(pow(p->next->x - x, 2) + pow(p->next->y - y, 2));
		if(num < min)
		{
			min = num;
			p2 = p;
		}
	}
	if(p2 == head)
	{
		p = (node *)malloc(sizeof(node));
		p->x = x;
		p->y = y;
		p->next = head->next;
		head->next = p;
		return p;
	}
	else{
		p = (node *)malloc(sizeof(node));
		p->x = x;
		p->y = y;
		p->next = p2->next;
		p2->next = p;
		return head;
	}
}


double findLength(node *head)
{
	if(head == NULL || head->next == head)
		return 0;
	double distance;
	node *p;
	distance = sqrt(pow(head->next->x - head->x, 2) + pow(head->next->y - head->y, 2));
	for(p = head->next; p != head; p = p->next)
	{
		distance += sqrt(pow(p->next->x - p->x, 2) + pow(p->next->y - p->y, 2));
	}
	return distance;
}

void printTour(node *head, double length, FILE *file)
{
	node *p;
	if(head == NULL)
		return;
	fprintf(file, "%lf\n", length);
	for(p = head->next; p != head; p = p->next)
	{
		fprintf(file, "%lf %lf\n", p->x, p->y);
	}
	fprintf(file, "%lf %lf\n", p->x, p->y);
}

void freeAll(node *head)
{
	if(head == NULL)
		return;
	node *p = head->next;
	node *p2;
	while(p != head)
	{
		p2 = p;
		p = p->next;
		free(p2);
	}
	free(p);
}
