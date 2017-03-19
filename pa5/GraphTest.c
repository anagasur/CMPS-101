//Katerina Chinnappan
//CruzID: kachinna
//PA 5

//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>

#include "Graph.c"
#include "List.c"

int main(int argc, char* argv[])
{
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);

   fprintf(stdout,"Number of verticies of G: %d \n\n", getOrder(G));
   fprintf(stdout,"------------Adjacency Matrix--------------\n\n\n");
   printGraph(stdout, G);

   fprintf(stdout, "------------DFS() on G called-------------\n\n\n");
   fprintf(stdout, "\n");
   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "------------Stack-------------\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   fprintf(stdout,"------------Copy of G: copyGraph() called--------------\n\n\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   fprintf(stdout,"------------Transpose of G: transpose() called--------------\n\n\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   fprintf(stdout, "------------DFS() on Transpose of G called-------------\n\n\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "------------Stack-------------\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
/*Output
Number of verticies of G: 8

------------Adjacency Matrix--------------


1: 2 5
2: 5 6
3: 2 4 6 7 8
4:
5:
6: 5 7
7:
8: 4 7
------------DFS() on G called-------------




x:  d  f  p
1:  1 10  0
2:  2  9  1
3: 11 16  0
4: 12 13  3
5:  3  4  2
6:  5  8  2
7:  6  7  6
8: 14 15  3

------------Stack-------------
3 8 4 1 2 6 7 5

------------Copy of G: copyGraph() called--------------


1: 2 5
2: 5 6
3: 2 4 6 7 8
4:
5:
6: 5 7
7:
8: 4 7

------------Transpose of G: transpose() called--------------


1:
2: 1 3
3:
4: 3 8
5: 1 2 6
6: 2 3
7: 3 6 8
8: 3

------------DFS() on Transpose of G called-------------



x:  d  f  p
1:  7  8  0
2:  9 10  0
3:  1  2  0
4:  5  6  0
5: 15 16  0
6: 11 12  0
7: 13 14  0
8:  3  4  0

------------Stack-------------
5 7 6 2 1 4 8 3

Process returned 0 (0x0)   execution time : 0.051 s
Press any key to continue.
*/

