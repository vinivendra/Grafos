

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"


void addEdge(graph G, int a, int b) {
    if (a < 0 || b < 0) {
        node *edge = malloc(sizeof(node));
        edge->value = b;
        edge->component = null;
        edge->next = G.list[a]->next;
        G.list[a]->next = edge;
        G.list[a]->value++;
    }
    else if (a > b) {
        node *edge = malloc(sizeof(node));
        edge->value = b;
        edge->component = null;
        edge->next = G.list[a]->next;
        G.list[a]->next = edge;
        G.list[a]->value++;
        
        node *edge2 = malloc(sizeof(node));
        edge2->value = a;
        edge2->component = null;
        edge2->next = G.list[b]->next;
        G.list[b]->next = edge2;
        G.list[b]->value++;
        
        edge->simetric = edge2;
        edge2->simetric = edge;
    }
}

void addDirectedEdge(graph G, int a, int b) {
    node *edge = malloc(sizeof(node));
    edge->value = b;
    edge->component = null;
    edge->next = G.list[a]->next;
    G.list[a]->next = edge;
    G.list[a]->value++;
}

void printGraph(graph G) {
    for (int i = 0; i < G.n; i++) {
        printf("%d -", i);
        for (node *p = G.list[i]->next; p != NULL; p = p->next) {
            printf(" %-2d", p->value);
        }
        printf("\n");
    }
}

void printComponents(graph G) {
    for (int i = 0; i < G.n; i++) {
        printf("%d -", i);
        for (node *p = G.list[i]->next; p != NULL; p = p->next) {
            printf(" %-2d", p->component);
        }
        printf("\n");
    }
}

void initGraphWithSize(graph *G, int n) {
    G->n = n;
    G->list = malloc(sizeof(node *) * n);
    for (int i = 0; i < n; i++) {
        node *p = malloc(sizeof(node));
        p->value = 0;
        p->component = null;
        p->simetric = NULL;
        p->next = NULL;
        G->list[i] = p;
    }
}


void destroyGraph(graph G) {
    for (int i = 0; i < G.n; i++) {
        for (node *p = G.list[i]; p != NULL;) {
            node *q = p;
            p = p->next;
            free(q);
        }
    }
    free(G.list);
}
