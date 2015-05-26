

#ifndef __EP2__unionFind__
#define __EP2__unionFind__


typedef struct unionFindSet {
    int *component;
    int *size;
} unionFindSet;

unionFindSet unionFindInit(int n);
int find(unionFindSet set, int a);
void unite(unionFindSet set, int a, int b);

#endif /* defined(__EP2__unionFind__) */
