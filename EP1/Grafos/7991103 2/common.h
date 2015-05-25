#ifndef __Grafos__common__
#define __Grafos__common__


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define null -1

#define true 1
#define false 0
typedef int bool;


typedef struct node {
    int value;
    int component;
    struct node *next;
    struct node *simetric;
} node;

typedef struct edge {
    int a;
    int b;
    node *node;
} edge;

typedef struct stackNode {
    edge e;
    struct stackNode *next;
} stackNode;


void printArray(int *a, int n);

int min(int a, int b);

#endif /* defined(__Grafos__common__) */
