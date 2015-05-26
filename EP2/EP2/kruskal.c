

#include <stdlib.h>

#include "kruskal.h"

#include "common.h"
#include "unionFind.h"


int compareNodes(const void *a, const void *b) {
    node *nodeA = *(node **)a;
    node *nodeB = *(node **)b;
    return nodeA->weight - nodeB->weight;
}


graph getKruskalMST(graph G) {

    int number_of_edges;
    node **edges = arrayOfEdges(G, &number_of_edges);

    qsort(edges, number_of_edges, sizeof(node *), compareNodes);

    printf("\n");
    for (int i = 0; i < number_of_edges; i++) {
        printf("%d-%d (%d) ",
               edges[i]->origin,
               edges[i]->destination,
               edges[i]->weight);
    }
    printf("\n");

    unionFindSet union_find_set = unionFindInit(G.number_of_vertices);

    graph T = newGraph(G.number_of_vertices);

    for (int i = 0; i < number_of_edges; i++) {
        int origin = min(edges[i]->origin, edges[i]->destination);
        int destination = max(edges[i]->origin, edges[i]->destination);
        int weight = edges[i]->weight;

        if (find(union_find_set, origin) != find(union_find_set, destination)) {
            addEdge(T, origin, destination, weight);
            unite(union_find_set, origin, destination);
        }
    }

    return T;
}
