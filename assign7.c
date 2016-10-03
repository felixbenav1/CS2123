/********************* Assignment 7 **************************
Purpose:
	This program reads a graph from a file and determines
	whether it is a tree by definition or not.
*************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct edgenode{
	int y;
	struct edgenode *next;
} edgenodeT;

typedef struct{
	edgenodeT *edges[101];
	int degree[101];
	int visited[101];
	int nvertices;
	int nedges;
} graphT;

void initializeGraph(graphT *g, int n, int m);
void insertEdge(graphT *g, int x, int y, int bool);
void DFS_graph(graphT *g, int v);
int checkGraph(graphT *g);
void freeGraph(graphT *g);

int main(int argc, char *argv[])
{
	graphT *myg1;
	FILE *file;
	int vertices, edges, i, x, y, j;
	
	if(argc != 2)
	{
		printf("Not enough arguments.\n");
		exit(-1);
	}
	
	file = fopen(argv[1], "r");
	if(file == NULL)
	{
		printf("File does not exist.\n");
		exit(-1);
	}
	
	fscanf(file, "%d %d", &vertices, &edges);
	if((vertices - edges) != 1 || vertices <= 0 || edges < 0)
	{
		//graph does not have n vertices and n-1 edges
		//or it has an incorrect amount of veritces
		printf("The graph does not belong to a tree.\n");
		fclose(file);
		return 0;
	}
	myg1 = (graphT *)malloc(sizeof(graphT));
	if(myg1 == NULL)
	{
		printf("Not enough memory.\n");
		exit(-1);
	}
	initializeGraph(myg1, vertices, edges);
	
	for(i = 1; i <= edges; i++)
	{
		j = fscanf(file, "%d %d", &x, &y);
		if(j != 2)
		{
			printf("Incorrect file format.\n");
			exit(-1);
		}
		insertEdge(myg1, x, y, 0);
	}
	
	DFS_graph(myg1, 1);	
	i = checkGraph(myg1);
	if(i == 1)
		printf("The graph does belong to a tree.\n");
	else
		printf("The graph does not belong to a tree.\n");
	
	freeGraph(myg1);
	fclose(file);
}


/*********************** initializeGraph ********************
Purpose:
	This function initializes a graph and its edges.
************************************************************/
void initializeGraph(graphT *g, int n, int m)
{
	int i;
	g->nvertices = n;
	g->nedges = m;
	
	for(i = 1; i <= 101; i++)
	{
		g->edges[i] = NULL;
		g->degree[i] = 0;
		g->visited[i] = 0;
	}
}


/********************** insertEdge *************************
Purpose:
	This function inserts an edge into a graph by using a
	from-vertex and a to-vertex.
***********************************************************/
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
	edgenodeT *p = g->edges[x];
	while(p != NULL)
	{
		if(e->y > p->y)
			p = p->next;
		else
			break;
	}
	e->next = p;
	p = e;
	g->degree[x]++;
	if(bool == 0)
		insertEdge(g, y, x, 1);				//insert the flipped point in as well (ex. 2 5 and 5 2)
}


/*********************** DFS_graph **************************
Purpose:
	This function starts at a given vertex and visits each
	component that is connected to it and putting a 1 to
	indicate that vertex has been visited.
************************************************************/
void DFS_graph(graphT *g, int v)
{
	edgenodeT *p;
	if(g == NULL)
		return;
	g->visited[v] = 1;		//1 to indicate vertex is visited
	
	p = g->edges[v];
	while(p != NULL)
	{
		if(g->visited[v] == 0)
			DFS_graph(g, p->y);		//check if vertex has not already been visited
		p = p->next;
	}
}


/************************** checkGraph ************************
Purpose:
	This funtion checks if a given graph is connected by
	checking if all of its vertices have been visited from 
	beginning to end.
**************************************************************/
int checkGraph(graphT *g)
{
	int i;
	
	for(i = 1; i <= g->nvertices; i++)
	{
		if(g->visited[i] == 0)
			return 0;		//0 means not visited meaning graph isn't connected
	}
	return 1;			//all vertices have been visited
}


/************************* freeGraph ***************************
Purpose:
	This function frees all memory allocated for a given graph.
***************************************************************/
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
