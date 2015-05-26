

#include <stdlib.h>

#include "dfs.h"


#define UNDISCOVERED -1


void recursiveDFS(graph T, int currentVertex, int discovery[], int *time);


int *getDFSDiscovery(graph T) {
    int *discovery = malloc(T.number_of_vertices * sizeof(int));
    for (int i = 0; i < T.number_of_vertices; i++)
        discovery[i] = UNDISCOVERED;

    int time = -1;

    for (int u = 0; u < T.number_of_vertices; u++) {
        if (discovery[u] == UNDISCOVERED) {
            discovery[u] = ++time;
            recursiveDFS(T, u, discovery, &time);
        }
    }

    return discovery;
}


void recursiveDFS(graph T, int currentVertex, int discovery[], int *time) {
    for (node *edge = T.edges[currentVertex]->next; edge != NULL;
         edge = edge->next) {
        int destination = edge->origin == currentVertex ? edge->destination
                                                        : edge->origin;
        if (discovery[destination] == UNDISCOVERED) {
            *time = *time + 1;
            int discoveryTime = *time;
            discovery[destination] = discoveryTime;
            recursiveDFS(T, destination, discovery, time);
        }
    }
}
