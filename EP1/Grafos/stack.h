#ifndef __Grafos__stack__
#define __Grafos__stack__

#include "common.h"

typedef stackNode* stack;

edge newEdge(int a, int b, node *node);
bool equalEdges(edge e, edge f);
void printEdge(edge e);

stack newStack();
void push(stack S, int a, int b, node *node);
bool empty(stack S);
edge pop(stack S);
edge top(stack S);
void printStack(stack S);
void destroyStack(stack S);


#endif /* defined(__Grafos__stack__) */
