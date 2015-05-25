

#include "stack.h"


edge newEdge(int a, int b, node *node) {
    edge e;
    e.a = a;
    e.b = b;
    e.node = node;
    return e;
}

edge nullEdge() {
    return newEdge(null, null, NULL);
}


bool equalEdges(edge e, edge f) {
    return (e.a == f.a && e.b == f.b);
}

void printEdge(edge e) {
    printf("[%-2d %2d]", e.a, e.b);
}


stack newStack() {
    stackNode *s = malloc(sizeof(stackNode));
    s->e = nullEdge();
    s->next = NULL;
    return s;
}


void push(stack S, int a, int b, node *node) {
    stackNode *element = malloc(sizeof(stackNode));
    element->e = newEdge(a, b, node);
    element->next = S->next;
    S->next = element;
}


bool empty(stack S) {
    return !(S->next);
}


edge pop(stack S) {
    if (empty(S)) return nullEdge();
    
    stackNode *pop = S->next;
    S->next = S->next->next;
    
    edge result = pop->e;
    
    free(pop);
    
    return result;
}


edge top(stack S) {
    if (empty(S)) return nullEdge();
    
    return S->next->e;
}


void printStack(stack S) {
    printf("Stack: ");
    for (stackNode *p = S->next; p != NULL; p = p->next) {
        printEdge(p->e);
        printf(" ");
    }
    printf("||\n");
}


void destroyStack(stack S) {
    while (!empty(S))
        pop(S);
    free(S);
}
