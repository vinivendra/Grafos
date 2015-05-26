

#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

graph newGraph(int number_of_vertices) {
    graph G;

    G.number_of_vertices = number_of_vertices;
    G.edges = malloc(number_of_vertices * sizeof(node *));

    for (int i = 0; i < number_of_vertices; i++) {
        node *edge = malloc(sizeof(node));
        edge->origin = -1;
        edge->destination = -1;
        edge->weight = -1;
        edge->next = NULL;
        G.edges[i] = edge;
        setDegree(G, i, 0);
    }

    return G;
}

void printGraph(graph G) {
    printf("\nGraph:");
    printf("\nVertices: %d", G.number_of_vertices);

    for (int i = 0; i < G.number_of_vertices; i++) {
        printf("\n%d: ", i);

        node *edge = G.edges[i];
        printf("[%d] -> [", getDegree(G, i));

        for (edge = edge->next; edge != NULL; edge = edge->next) {
            printf("%d (%d)", edge->destination, edge->weight);
            if (edge->next != NULL) {
                printf(", ");
            }
        }
        printf("]");
    }

    printf("\n");
}

void addEdge(graph G, int origin, int destination, int weight) {
    addDirectedEdge(G, origin, destination, weight);
    addDirectedEdge(G, destination, origin, weight);
}

void addDirectedEdge(graph G, int origin, int destination, int weight) {
    node *edge = malloc(sizeof(node));
    edge->origin = origin;
    edge->destination = destination;
    edge->weight = weight;

    edge->next = G.edges[origin]->next;
    G.edges[origin]->next = edge;

    increaseDegree(G, origin);
}

int getDegree(graph G, int vertex) {
    return G.edges[vertex]->weight;
}

void setDegree(graph G, int vertex, int new_degree) {
    G.edges[vertex]->weight = new_degree;
}

void increaseDegree(graph G, int vertex) {
    G.edges[vertex]->weight++;
}

node **arrayOfEdges(graph G, int *number_of_edges) {
    *number_of_edges = 0;

    for (int i = 0; i < G.number_of_vertices; i++) {
        *number_of_edges += getDegree(G, i);
    }

    node **arrayOfEdges = malloc(*number_of_edges * sizeof(node *));

    int currentEdge = 0;
    for (int i = 0; i < G.number_of_vertices; i++) {
        for (node *edge = G.edges[i]->next; edge != NULL; edge = edge->next) {
            arrayOfEdges[currentEdge] = edge;
            currentEdge++;
        }
    }

    return arrayOfEdges;
}

void freeGraph(graph G) {
    for (int i = 0; i < G.number_of_vertices; i++) {
        node *edge = G.edges[i];
        while (edge != NULL) {
            G.edges[i] = G.edges[i]->next;
            free(edge);
            edge = G.edges[i];
        }
    }

    free(G.edges);
}