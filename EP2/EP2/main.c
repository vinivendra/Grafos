

#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "common.h"
#include "graph.h"
#include "kruskal.h"
#include "dfs.h"


int main(int argc, const char *argv[]) {

    bool testSucceeded = runTests();

    if (testSucceeded) {

        int n;
        scanf("%d", &n);

        graph G = newGraph(n);

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int weight;
                scanf("%d", &weight);
                if (u != v) {
                    addDirectedEdge(G, u, v, weight);
                }
            }
        }

        printGraph(G);

        graph T = getKruskalMST(G);

        printGraph(T);

        int *discovery = getDFSDiscovery(T);

        printf("\ndiscovery: [");
        for (int i = 0; i < T.number_of_vertices - 1; i++) {
            printf("%d, ", discovery[i]);
        }
        printf("%d]\n", discovery[T.number_of_vertices - 1]);

        int *TSPCycle = malloc(T.number_of_vertices * sizeof(int));
        for (int i = 0; i < T.number_of_vertices; i++) {
            TSPCycle[discovery[i]] = i;
        }

        printf("\nTSP: [");
        for (int i = 0; i < T.number_of_vertices - 1; i++) {
            printf("%d, ", TSPCycle[i]);
        }
        printf("%d]\n", TSPCycle[T.number_of_vertices - 1]);


        printf("==================\n");
        for (int i = 0; i < T.number_of_vertices; i++) {
            for (node *edge = T.edges[i]->next; edge != NULL;
                 edge = edge->next) {
                if (edge->origin < edge->destination)
                    printf("%d %d\n", edge->origin, edge->destination);
            }
        }

        for (int i = 0; i < T.number_of_vertices; i++) {
            printf("%d ", TSPCycle[i]);
        }
        printf("0\n");
    }

    return 0;
}
