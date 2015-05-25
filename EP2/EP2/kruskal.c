

#include "kruskal.h"

#include "common.h"

#include <stdlib.h>


int compareNodes(const void *a, const void *b) {
    node *nodeA = *(node **)a;
    node *nodeB = *(node **)b;
    return nodeA->weight - nodeB->weight;
}


graph getKruskalMST(graph G) {

    int number_of_edges;
    node **edges = arrayOfEdges(G, &number_of_edges);

    qsort(edges, number_of_edges, sizeof(node *), compareNodes);

    int *components = malloc(G.number_of_vertices * sizeof(int));
    for (int i = 0; i < G.number_of_vertices; i++)
        components[i] = i;

    graph T = newGraph(G.number_of_vertices);

    for (int i = 0; i < number_of_edges; i += 2) {
        int origin = min(edges[i]->origin, edges[i]->destination);
        int destination = max(edges[i]->origin, edges[i]->destination);
        int weight = edges[i]->weight;

        if (components[origin] != components[destination]) {
            addEdge(T, origin, destination, weight);

            int newComponent
            = min(components[destination], components[origin]);
            components[destination] = components[origin] = newComponent;
        }
    }

    return T;
}

