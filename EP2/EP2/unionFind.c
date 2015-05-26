

#include <stdlib.h>

#include "unionFind.h"


unionFindSet unionFindInit(int n) {
    unionFindSet set;
    set.component = malloc(n * sizeof(int));
    set.size = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        set.component[i] = i;
        set.size[i] = 1;
    }

    return set;
}


int find(unionFindSet set, int a) {
    while (set.component[a] != a)
        a = set.component[a];
    return a;
}


void unite(unionFindSet set, int a, int b) {
    a = find(set, a);
    b = find(set, b);

    if (set.size[a] < set.size[b]) {
        set.component[a] = b;
        set.size[b] += set.size[a];
    }
    else {
        set.component[b] = a;
        set.size[a] += set.size[b];
    }
}

