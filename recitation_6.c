/************************** Recitation 6 ****************************

********************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct edgenodeT{
	int y;
	struct edgenodeT *next;
} edgenodeT;

typedef struct{
	edgenodeT *edges[101];
	int degree[101];
	int visited[101];
	int nvertices;
	int nedges;
} graphT;

void initializeGraph(graphT *g, int n, int m);
edgenodeT *insertNode(edgenodeT *p, int i);
int goOutside(graphT *g, edgenodeT *l1, edgenodeT *l2, int i, int *c1, int c2);
void freeList(edgenodeT *p, int i);
void insertEdge(graphT *g, int x, int y, int bool);
void freeGraph(graphT *g);

int main(int argc, char *argv[])
{
	FILE *file;
	graphT *myg1;
	int i, j, x, y, vertices, edges;
	
	if(argc != 2)
	{
		printf("Not enough arguments.\n");
		return 0;
	}
	
	file = fopen(argv[1], "r");
	if(file == NULL)
	{
		printf("File does not exist.\n");
		return 0;
	}
	
	i = fscanf(file, "%d %d", &vertices, &edges);
	if(i != 2)
	{
		printf("Incorrect file format.\n");
		return 0;
	}
	if(vertices <= 0 || edges < 0)
	{
		printf("Not enough information for graph.\n");
		return 0;
	}
	myg1 = (graphT *)malloc(sizeof(graphT));
	if(myg1 == NULL)
	{
		printf("Not enough memory.\n");
		return 0;
	}
	initializeGraph(myg1, vertices, edges);
	for(i = 0; i < myg1->nedges; i++)
	{
		j = fscanf(file, "%d %d", &x, &y);
		if(j != 2)
		{
			printf("Incorrect file format.\n");
			freeGraph(myg1);
			return 0;
		}
		insertEdge(myg1, x, y, 0);
	}
	if(myg1->edges[1] == NULL)
	{
		//1 isnt connected
	}
	edgenodeT *list1 = NULL;
	edgenodeT *list2 = NULL;
	int c1 = edges + 1;
	int c2 = 0;
	for(i = 2; i <= myg1->nvertices; i++)
	{
		goOutside(myg1, list1, list2, i, &c1, c2);
		//clearVisited(myg1, 1);
		freeList(list1, -1);
		freeList(list2, -1);
	}
	
	freeGraph(myg1);
	fclose(file);
}


int goOutside(graphT *g, edgenodeT *l1, edgenodeT *l2, int i, int *c1, int c2)
{
	edgenodeT *p;
	int j;
	if(c2 > g->nedges || g->edges[i] == NULL)
	{
		return 0;
	}
	if(c2 < *c1 && i == 1)
	{
		freeList(l1, -1);
		copyList(&l1, l2);
		*c1 = c2;
		return 1;
	}
	
	g->visited[i] = 1;
	for(p = g->edges[i]; p != NULL; p = p->next)
	{
		if(g->visited[p->y] == 0)
		{
			l2 = insertNode(l2, p->y);
			j = goOutside(g, l1, l2, p->y, c1, c2 + 1);
			//clearVisited()
			if(j == 1)
				return 0;
			freeList(l2, p->y);
		}
	}
	return 0;
}


edgenodeT *insertNode(edgenodeT *p, int i)
{
	if(p == NULL)
	{
		edgenodeT *e;
		e = (edgenodeT *)malloc(sizeof(edgenodeT));
		if(e == NULL)
		{
			printf("Not enough memory.\n");
			exit(-1);
		}
		e->y = i;
		e->next = NULL;
		return e;
	}
	p->next = insertNode(p->next, i);
	return p;
}


void initializeGraph(graphT *g, int n, int m)
{
	int i;
	
	g->nvertices = n;
	g->nedges = m;
	
	for(i = 1; i <= 100; i++)
	{
		g->edges[i] = NULL;
		g->degree[i] = 0;
		g->visited[i] = 0;
	}
}


void insertEdge(graphT *g, int x, int y, int bool)
{
	edgenodeT *e;
	e = (edgenodeT *)malloc(sizeof(edgenodeT));
	if(e == NULL)
	{
		printf("Not enough memory.\n");
		exit(-1);
	}
	e->y = y;
	e->next = NULL;
	edgenodeT **p = &g->edges[x];
	edgenodeT **pprecedes = NULL;
	while((*p) != NULL)
	{
		if(e->y >= (*p)->y){
			pprecedes = p;
			p = &(*p)->next;
		}
		else
			break;
	}
	if(pprecedes == NULL)
	{
		e->next = (*p);
		(*p) = e;
	}
	else{
		e->next = (*pprecedes)->next;
		(*pprecedes)->next = e;
	}
	g->degree[x]++;
	if(bool == 0)
		insertEdge(g, y, x, 1);				//insert the flipped point in as well (ex. 2 5 and 5 2)
}


void freeGraph(graphT *g)
{
	edgenodeT *p, *e;
	int i;
	
	for(i = 1; i <= g->nvertices; i++)
	{
		//free edge adjacency list
		e = g->edges[i];
		while(p != NULL)
		{
			e = p;
			p = p->next;
			free(e);
		}
	}
	//free entire graph
	free(g);
}


void freeList(edgenodeT *p, int i)
{
	edgenodeT *e;
	if(i == -1)
	{	
		while(p != NULL)
		{
			e = p;
			p = p->next;
			free(e);
		}
	}
	else{
		while(p->y != i)
		{
			p = p->next;
		}
		p = p->next;
		while(p != NULL)
		{
			e = p;
			p = p->next;
			free(e);
		}
	}
}
