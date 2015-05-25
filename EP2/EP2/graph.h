

#ifndef __EP2__graph__
#define __EP2__graph__

#include <stdio.h>

typedef struct node {
    int origin;
    int destination;
    int weight;
    struct node *next;
} node;

typedef struct graph {
    int number_of_vertices;
    node **edges;
} graph;

graph newGraph(int number_of_vertices);
void printGraph(graph G);
void addEdge(graph G, int origin, int destination, int weight);
void addDirectedEdge(graph G, int origin, int destination, int weight);

int getDegree(graph G, int vertex);
void setDegree(graph G, int vertex, int new_degree);
void increaseDegree(graph G, int vertex);

node **arrayOfEdges(graph G, int *number_of_edges);

#endif /* defined(__EP2__graph__) */
