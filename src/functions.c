#include <stdlib.h>
#include <stdio.h>

#include "../include/functions.h"

list meeting(team *t) {
    int *visited = (int *) calloc(t->size, sizeof(int));
    list l;
    
    make_empty_list(&l);
    for(int i = 0; i < t->size; i++){
        if(visited[i] == 0)
            topological_order(t, visited, i, &l);
    }
    return l;
}

void topological_order(team *t, int *visited, int node, list *l) {
    cell *p = t->adjacency[node].start->next;
    visited[node] = 1;
    
    while(p != NULL) {
        if(visited[p->item] == 0)
            topological_order(t, visited, p->item, l);
        p = p->next;
    }
    add_item_start(l, node);
}