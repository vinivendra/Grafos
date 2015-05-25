

#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "common.h"
#include "graph.h"
#include "kruskal.h"


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
                if (weight != 0) {
                    addDirectedEdge(G, u, v, weight);
                }
            }
        }

        printGraph(G);

        graph T = getKruskalMST(G);

        printGraph(T);
    }

    return 0;
}
