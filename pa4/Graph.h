//Katerina Chinnappan
//CruzID: kachinna
//PA 4

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
/***macros****/
#define NIL -2
#define INF -1
#include "List.h"
// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
#endif // GRAPH_H_INCLUDED
