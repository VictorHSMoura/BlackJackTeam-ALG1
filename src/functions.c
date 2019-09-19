#include <stdlib.h>
#include <stdio.h>

#include "../include/functions.h"

void meeting(team *t) {
    int *visited = (int *) calloc(t->size, sizeof(int));
    for(int i = t->size - 1; i >= 0; i--){
        if(visited[i] == 0)
            topological_order(t, visited, i);
    }
}

void topological_order(team *t, int *visited, int node) {
    cell *p = t->adjacency[node].start->next;
    visited[node] = 1;
    while(p != NULL) {
        if(visited[p->item] == 0)
            topological_order(t, visited, p->item);
        p = p->next;
    }
    printf("%d\n", node+1);
}