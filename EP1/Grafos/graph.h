#ifndef __Grafos__graph__
#define __Grafos__graph__



#include "common.h"

typedef struct graph {
    node **list;
    int n;
} graph;

void addDirectedEdge(graph G, int a, int b);
void addEdge(graph G, int a, int b);
void printGraph(graph G);
void printComponents(graph G);
void initGraphWithSize(graph *G, int n);
void destroyGraph(graph G);



#endif /* defined(__Grafos__graph__) */
