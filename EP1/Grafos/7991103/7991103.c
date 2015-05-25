

#include "common.h"
#include "graph.h"
#include "stack.h"

int n;
int t;
int c;
int *f;
int *p;
int *low;
int *d;
int *cut;
graph components;
stack s;

void DFS_VISIT(graph G, int u) {

    d[u] = t++;
    low[u] = d[u];

    int filhos = 0;

    for (node *q = G.list[u]->next; q != NULL; q = q->next) {
        int v = q->value;

        if (p[v] == null) {
            p[v] = u;
            filhos++;

            push(s, u, v, q);

            DFS_VISIT(G, v);

            if (low[v] >= d[u]) {
                edge uv = newEdge(u, v, q);
                while (!empty(s)) {
                    edge e = pop(s);
                    e.node->component = c;
                    e.node->simetric->component = c;

                    if (cut[e.a])
                        addDirectedEdge(components, c, n + e.a);
                    if (cut[e.b])
                        addDirectedEdge(components, c, n + e.b);

                    if (equalEdges(e, uv))
                        break;
                }
                if (!empty(s)) {
                    cut[u] = true;
                    addDirectedEdge(components, c, n + u);
                }
                c++;
            }
            low[u] = min(low[u], low[v]);
        }
        // Arco de retorno não-pai
        else if ((p[u] != v) && (d[v] < d[u])) {
            push(s, u, v, q);
            low[u] = min(low[u], d[v]);
        }
    }

    if (p[u] == u) {
        if (filhos > 1) {
            cut[u] = true;
            for (node *q = G.list[u]->next; q != NULL; q = q->next) {
                if (q->component != null) {
                    addDirectedEdge(components, q->component, n + u);
                }
            }
        }
    }

    f[u] = t++;
}

void DFS(graph G) {

    // Initialization
    initGraphWithSize(&components, 2 * n);

    t = 1;
    c = 0;

    f = malloc(n * sizeof(int));
    p = malloc(n * sizeof(int));
    d = malloc(n * sizeof(int));
    low = malloc(n * sizeof(int));
    cut = malloc(n * sizeof(int));
    int *repeat = malloc(n * sizeof(int));

    s = newStack();

    for (int i = 0; i < n; i++) {
        f[i] = p[i] = d[i] = low[i] = null;
        cut[i] = false;
        repeat[i] = false;
    }


    // DFS
    for (int i = 0; i < n; i++) {
        if (f[i] == null) {
            p[i] = i;
            DFS_VISIT(G, i);
        }
    }


    // Rename the cut vertices
    int v = c;
    for (int i = 0; i < n; i++) {
        if (cut[i]) {
            cut[i] += v - 1;
            v++;
        }
    }

    // Remove repeated vertices from the new graph
    for (int i = 0; i < n; i++) {
        node *q = components.list[i];
        for (node *p = components.list[i]->next; p != NULL;) {
            int vertex = p->value - n;
            if (repeat[vertex]) {
                node *r = p;
                q->next = p->next;
                p = p->next;
                free(r);
            } else {
                repeat[vertex] = true;
                p = p->next;
                q = q->next;
            }
        }
        for (node *p = components.list[i]->next; p != NULL; p = p->next) {
            int vertex = p->value - n;
            repeat[vertex] = false;
        }
    }

    // Rename the cut vertices in the new graph
    for (int i = 0; i < n; i++) {
        for (node *p = components.list[i]->next; p != NULL; p = p->next) {
            int vertex = p->value - n;
            p->value = cut[vertex];
        }
    }

    // Add the simetric edges missing in the new graph
    for (int i = 0; i < c; i++) {
        for (node *p = components.list[i]->next; p != NULL; p = p->next) {
            addDirectedEdge(components, p->value, i);
        }
    }

    // Rename the components
    graph H;
    initGraphWithSize(&H, n);

    for (int i = 0; i < n; i++) {
        for (node *p = G.list[i]->next; p != NULL; p = p->next) {
            addDirectedEdge(H, i, p->value);
            H.list[i]->next->component = c - p->component - 1;
        }
    }

    graph K;
    initGraphWithSize(&K, v);

    for (int i = 0; i < v; i++) {
        for (node *p = components.list[i]->next; p != NULL; p = p->next) {
            if (i < c) {
                addDirectedEdge(K, c - i - 1, p->value);
            } else {
                addDirectedEdge(K, i, c - p->value - 1);
            }
        }
    }

    graph J;
    initGraphWithSize(&J, v);
    for (int i = 0; i < v; i++) {
        for (node *p = K.list[i]->next; p != NULL; p = p->next) {
            addDirectedEdge(J, i, p->value);
        }
    }


    // Output
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d", H.list[i]->value);
        for (node *p = H.list[i]->next; p != NULL; p = p->next) {
            printf(" %d", p->component);
        }
        printf("\n");
    }

    printf("%d\n", v - c);
    for (int i = 0; i < n; i++) {
        if (cut[i]) {
            printf("%d %d\n", i, cut[i]);
        }
    }

    printf("%d\n", v);
    for (int i = 0; i < v; i++) {
        printf("%d", J.list[i]->value);
        for (node *p = J.list[i]->next; p != NULL; p = p->next) {
            printf(" %d", p->value);
        }
        printf("\n");
    }


    // Frees
    free(f);
    free(p);
    free(d);
    free(low);
    free(cut);
    free(repeat);
    destroyStack(s);
    destroyGraph(H);
    destroyGraph(K);
    destroyGraph(J);
    destroyGraph(components);
}


int main(int argc, const char *argv[]) {

    while (scanf("%d", &n) != EOF) {
        graph G;
        initGraphWithSize(&G, n);

        for (int i = 0; i < n; i++) {
            int degree;
            scanf("%d", &degree);

            for (int j = 0; j < degree; j++) {
                int edge;
                scanf("%d", &edge);
                addEdge(G, i, edge);
            }
        }

        DFS(G);

        destroyGraph(G);
    }


    return 0;
}
