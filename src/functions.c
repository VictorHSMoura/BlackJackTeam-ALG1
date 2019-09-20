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

int swap(team *t, int src, int dest) {
    cell *edge = find(&t->adjacency[src], dest);

    if (edge != NULL) {
        remove_by_pointer(&t->adjacency[src], edge);
        add_item_end(&t->adjacency[dest], src);

        if (verify_cycle(t)) {
            remove_item_end(&t->adjacency[dest]);
            add_item_by_pointer(&t->adjacency[src], edge, dest);
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}

int verify_cycle(team *t) {
    int *visited = (int *) calloc(t->size, sizeof(int));

    for(int i = 0; i < t->size; i++) {
        if(visited[i] == 0)
            if(dfs_cycle(t, visited, i))
                return 1;
    }
    return 0;
}

int dfs_cycle(team *t, int *visited, int node) {
    cell *p = t->adjacency[node].start->next;
    visited[node] = 1;

    while (p != NULL) {
        if(visited[p->item] == 1)
            return 1;
        else if(dfs_cycle(t, visited, p->item))
            return 1;
        p = p->next;
    }
    visited[node] = 2;
    return 0;
}