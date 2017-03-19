//Katerina Chinnappan
//CruzID: kachinna
//PA 4

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
/***macros to keep track of colors****/
#define WHITE 1
#define GRAY 2
#define BLACK 3

struct GraphObj{
   List *adj; //An array of Lists whose ith element contains the neighbors of vertex
   int *color; //An array of ints (or chars, or strings) whose ith ele
   int *parent; //An array of ints whose ith element is the parent o
   int *distance; //An array of ints whose ith element is the distance
   int order; //the number of vertices
   int size; //the number of edges
   int source;//label of the vertex that was most recently used as source for BFS
};
// returns a Graph pointing to a newly created GraphObj representing a graph having
//n vertices and no edges.
// all arrays be of length n+1
//,where n is the number of vertices in the graph,
//and that only indices 1 through n be used.
//This is so that array indices can be directly identified with vertex labels.
Graph newGraph(int n){
    Graph graph = malloc(sizeof(struct GraphObj));
    graph->adj = calloc(n+1, sizeof(List));
    graph->color = calloc(n+1, sizeof(int));
    graph->parent = calloc(n+1, sizeof(int));
    graph->distance = calloc(n+1, sizeof(int));
    graph->order = n;
    graph->size = 0;
    graph->source = NIL;

    int i;
    for(i = 0; i<(n+1); i++)
    {
        graph->adj[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->distance[i] = INF;
    }

    return graph;

}
//frees all dynamic memory associated with the Graph
//*pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG){
    Graph temp = *pG;
    int i;
    for(i = 0; i<(temp->order + 1); i++)
    {
        freeList(&(temp->adj[i]));
    }


    free(temp->adj);
    free(temp->parent);
    free(temp->distance);
    free(temp->color);

    free(*pG);
    *pG = NULL;
}
/****ACCESS FUNCTIONS START HERE*****/
//returns the number of vertices
int getOrder(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getOrder()");
        exit(1);
    }
    return G->order;
}
//returns the number of edges
int getSize(Graph G){
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getSize()");
        exit(1);
    }
    return G->size;
}
//returns the source of a graph
int getSource(Graph G){
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getSource()");
        exit(1);
    }
    return G->source;
}
// return the parent of vertex u in the BreadthFirst
//tree created by BFS(), or NIL if BFS() has not yet been called
int getParent(Graph G, int u){
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getParent()");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getParent() vertex out of bounds");
        exit(1);
    }
    return G->parent[u];
}
//returns the distance from the most recent BFS source to vertex u,
//or INF if BFS() has not yet been called.
int getDist(Graph G, int u){
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getDist()");
        exit(1);
    }
    if(getSource(G) == NIL)
    {
      return INF;
    }
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getDist() vertex out of bounds");
        exit(1);
    }

    return G->distance[u];
}
//appends to the List L the vertices of a shortest path in G from source to u, or appends to L the
//value NIL if no such path exists. getPath() has the precondition getSource(G)!=NIL, so BFS() must
//be called before getPath().
void getPath(List L, Graph G, int u){
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getPath()");
        exit(1);
    }

    if(getSource(G) == NIL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getPath() on NULL source");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call getPath() on NULL source");
        exit(1);
    }
    if(u == G->source)
    {
        prepend(L, G->source);
    }
    else if(G->parent[u] == NIL)
    {
        append(L, NIL);
    }
    else
    {
        getPath(L, G, G->parent[u]);
        prepend(L,u);
    }
}
/****ACCESS FUNCTIONS END HERE*****/

/*** MANIPULATION PROCEDURES START HERE ***/
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call makeNull(Graph G)");
        exit(1);
    }
    int i;
    for(i = 0; i < (G->order + 1); i++)
    {
        clear(G->adj[i]);
    }
}
// inserts a new edge joining u to v, i.e. u is added to the
//adjacency List of v, and v to the adjacency List of u
void addEdge(Graph G, int u, int v){
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call addEdge(Graph G, int u, int v)");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call addEdge(Graph G, int u, int v), out of bounds");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call addEdge(Graph G, int u, int v), out of bounds");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}
// inserts a new directed edge from u to v, i.e. v is added to the
//adjacency List of u (but not u to the adjacency List of v)
void addArc(Graph G, int u, int v){
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call addArc(Graph G, int u, int v)");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call addArc(Graph G, int u, int v), out of bounds");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call addArc(Graph G, int u, int v), out of bounds");
        exit(1);
    }

    moveFront(G->adj[u]);
    while(index(G->adj[u]) > -1 && v > get(G->adj[u]))
    {
        moveNext(G->adj[u]);
    }
    if(index(G->adj[u]) ==  -1)
    {
        append(G->adj[u], v);
    }
    else
        insertBefore(G->adj[u], v);

    G->size++;
}
//runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
//and source fields of G accordingly.
void BFS(Graph G, int s){
    if(G == NULL)
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call BFS(Graph G, int s");
        exit(1);
    }
    if(s < 1 || s > getOrder(G))
    {
        fprintf(stderr, "Invalid(Graph Usage): cannot call BFS(Graph G, int s), out of bounds");
    }

    int i;
    for(i = 0; i < (G->order +1); i++)
    {
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = WHITE;
    }

    List Q = newList();
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;
    prepend(Q,s);

    while(length(Q) > 0)
    {
        int temp = back(Q);
        deleteBack(Q);

        moveFront(G->adj[temp]);


        while(index(G->adj[temp]) > -1)
        {
            int u = get(G->adj[temp]);

            if(G->color[u] == WHITE)
            {
                G->color[u] =  GRAY;
                G->parent[u] = temp;
                G->distance[u] = G->distance[temp] + 1;
                prepend(Q,u);
            }
            moveNext(G->adj[temp]);
        }
    }
    freeList(&Q);
}
//prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){
    if(out == NULL || G == NULL) {
      printf("Invalid(Graph Usage): cannot call printGraph(FILE *out, Graph G");
      exit(1);
   }
   int i;
   for(i = 1; i <= getOrder(G); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
   }
}
/*** MANIPULATION PROCEDURES END HERE ***/
