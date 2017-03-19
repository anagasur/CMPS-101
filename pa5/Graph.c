//Katerina Chinnappan
//CruzID: kachinna
//PA 5

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

#include "Graph.h"


#define WHITE 0
#define GRAY 1
#define BLACK 2

struct GraphObj {
   List *adj;
   int *color;
   int *parent;
   int *discover;
   int *finish;
   int order;
   int size;
   int time;
};

// Returns a pointer to a new GraphObj
 Graph newGraph(int n) {
    Graph G = malloc(sizeof(struct GraphObj));
    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->time = UNDEF;

    int i;
    for(i = 0; i<(n+1); i++)
    {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    return G;

}

// Frees memory allocate to a GraphObj
 void freeGraph(Graph *pG) {
       Graph temp = *pG;

    int i;
    for(i = 0; i<(temp->order + 1); i++)
    {
        freeList(&(temp->adj[i]));
    }


    free(temp->adj);
    free(temp->parent);
    free(temp->discover);
    free(temp->finish);
    free(temp->color);

    free(*pG);
    *pG = NULL;

}

// Returns the number of verticies in the Graph
 int getOrder(Graph G) {
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call getOrder()");
        exit(1);
    }
    return G->order;
}

// Returns the number of edges in the Graph
 int getSize(Graph G) {
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call getSize()");
        exit(1);
    }
    return G->size;
}

// Returns the parent of a given vertex
// Pre: 1 <= u <= getOrder(G)
 int getParent(Graph G, int u) {
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call getParent()");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid: cannot call getParent() vertex out of bounds");
        exit(1);
    }
    return G->parent[u];
}

// Returns the discover time
// Pre: 1 <= u <= getOrder(G)
 int getDiscover(Graph G, int u) {
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call getDiscover()");
        exit(1);
    }

    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid: cannot call getDiscover() vertex out of bounds");
        exit(1);
    }

    return G->discover[u];
}

// Returns the finish time
// Pre: 1 <= u <= getOrder(G)
 int getFinish(Graph G, int u) {
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call getFinish()");
        exit(1);
    }


    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid: cannot call getFinish() on NULL source");
        exit(1);
    }

    return G->finish[u];


}

// Adds an undirected edge to the Graph G from u to v
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
 void addEdge(Graph G, int u, int v) {
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call addEdge(Graph G, int u, int v)");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid: cannot call addEdge(Graph G, int u, int v), out of bounds");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        fprintf(stderr, "Invalid: cannot call addEdge(Graph G, int u, int v), out of bounds");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, u, v);
    G->size--;
}

// Adds a directed edge to the Graph G from u to v
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
 void addArc(Graph G, int u, int v) {
     if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call addArc(Graph G, int u, int v)");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid: cannot call addArc(Graph G, int u, int v), out of bounds");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        fprintf(stderr, "Invalid: cannot call addArc(Graph G, int u, int v), out of bounds");
        exit(1);
    }

    List L = G->adj[u];

    if(isEmpty(L))
    {
        append(L, v);
        G->size++;
        return;
    }
    moveTo(L, 0);
    while(index1(L) != -1)
    {
        if(v == get(L))
        {
            return;
        }
        if(v < get(L))
        {
            insertBefore(L, v);
            G->size++;
            return;
        }
        moveNext(L);
    }
    append(L, v);
    G->size++;


}

//helper for DFS()
 void Visit(Graph G, int x, List L)
{
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call Visit(Graph G, int x, List L)");
        exit(1);
    }
    int y;
    //color[x] = gray
    G->color[x] = GRAY;
    //d[x] = (++time)
    G->time++;
    G->discover[x] = G->time;
    List S = G->adj[x];
    //for all y belong to all adj[x]
    for(moveTo(S, 0); index1(S) != -1; moveNext(S))
    {
        y = get(S);

        //if color[y] == white
        if(G->color[y] == WHITE)
        {
            //p[y] = x
            G->parent[y] = x;
            //Visit(G, y, L
            Visit(G, y, L);
        }
    }

    //color[x] = black
    G->color[x] = BLACK;
    //f[x] = (++time)
    G->time++;
    G->finish[x] = G->time;
    prepend(L, x);
}
//performs the depth first search algorithm on G
 void DFS(Graph G, List S)
{
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call DFS(Graph G, List S)");
        exit(1);
    }

    if(length(S) != getOrder(G))
    {
        printf("Invalid: cannot call DFS() without equal sizes\n");
        exit(1);
    }

    List temp = copyList(S);
    clear(S);
    int i;
    int x;
    //for all x in V
    for(i = 1; i < G->order; i++)
    {
        //color[x] =  white
        G->color[i] = WHITE;
        //p[x] = nil
        G->parent[i] = NIL;
        //d[x] = undefined
        G->discover[i] =  UNDEF;
        //f[x] = undefined
        G->finish[i] = UNDEF;
    }
    //time = 0
    G->time = 0;

    //for all x in V
    for(moveTo(temp, 0); index1(temp) != -1; moveNext(temp))
    {
        x = get(temp);
        //if color[x] == white
        if(G->color[x] == WHITE)
        {
            //Visit(G, x, S)
            Visit(G, x, S);
        }
    }
    freeList(&temp);

}

// Prints out the Graph by iterating over and printing out
// each adjacency list with the row number preceeding it.
 void printGraph(FILE* out, Graph G)
{
	if( G == NULL){
		printf("Graph Error: printGraph() called on a NULL graph reference");
		exit(1);
	}
   if( G==NULL )
   {
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(1);
   }
   int i;
	for(i = 1; i<=getOrder(G); i++)
	{
		fprintf(out,"%d: ",i);
		printList(out, G->adj[i]);
				fprintf(out, "\n");
	}
}

 Graph transpose(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call transpose(Graph G)");
        exit(1);
    }
    Graph Transpose = newGraph(getOrder(G));

    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        moveFront(G->adj[i]);
        while(index1(G->adj[i])>= 0)
            {
                addArc(Transpose, get(G->adj[i]), i);
                moveNext(G->adj[i]);
            }
    }
    return Transpose;
}

 Graph copyGraph(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Invalid: cannot call copyGraph(Graph G)");
        exit(1);
    }

    Graph Copy = newGraph(getOrder(G));
    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        moveFront(G->adj[i]);

        while(index1(G->adj[i]) >= 0)
        {
            addArc(Copy, i, get(G->adj[i]));
            moveNext(G->adj[i]);
        }
    }
    return Copy;
}
/*****extra from pa4*****/
/*void printPath(FILE* out, Graph G, int x, int y)
{
    int parent = getParent(G, y);

    if(y == x)
    {
        fprintf(out, "%d", x);
        fprintf(out, "\n");
    }
    else if(parent == NIL)
    {
        fprintf(out, "No %d-%d path exists\n", x, y);
    }
    else
    {
        printPath(out, G, x, parent);
        fprintf(out, "%d", y);
        fprintf(out, "\n");
    }
}*/
