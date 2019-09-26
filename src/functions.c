#include <stdlib.h>
#include <stdio.h>

#include "../include/functions.h"

list meeting(team *t) {
    int *visited = (int *) calloc(t->size, sizeof(int));
    list l;
    
    make_empty_list(&l);
    for(int i = 0; i < t->size; i++){
        if(visited[i] == WHITE)
            topological_order(t, visited, i, &l);
    }
    return l;
}

void topological_order(team *t, int *visited, int node, list *l) {
    cell *p = t->adjacency[node].start->next;
    visited[node] = GRAY;
    
    while(p != NULL) {
        if(visited[p->item] == WHITE)
            topological_order(t, visited, p->item, l);
        p = p->next;
    }
    add_item_start(l, node + OFFSET);
    visited[node] = BLACK;
}

int swap(team *t, int src, int dest) {
    src = src - OFFSET;
    dest = dest - OFFSET;
    cell *edge = find(&t->adjacency[src], dest);

    if (edge == NULL) { 
        int aux;
        aux = src; src = dest; dest = aux;
        edge = find(&t->adjacency[src], dest);
    }
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
        if(visited[i] == WHITE)
            if(dfs_cycle(t, visited, i))
                return 1;
    }
    return 0;
}

int dfs_cycle(team *t, int *visited, int node) {
    cell *p = t->adjacency[node].start->next;
    visited[node] = GRAY;

    while (p != NULL) {
        if(visited[p->item] == GRAY)
            return 1;
        else if(visited[p->item] == WHITE)
            if(dfs_cycle(t, visited, p->item))
                return 1;
        p = p->next;
    }
    visited[node] = BLACK;
    return 0;
}

team invert_edges(team *t) {
    team inverted_team;
    make_empty_team(&inverted_team, t->size);

    for(int i = 0; i < t->size; i++) {
        list edges = t->adjacency[i];
        for (cell *p = edges.start->next; p != NULL; p = p->next) {
            insert_edge(&inverted_team, p->item + OFFSET, i + OFFSET);
        }
        set_age(&inverted_team, i, t->ages[i]);
    }
    return inverted_team;
}

int commander(team *t, int node) {
    team inverted_team = invert_edges(t);
    int *visited = (int *) calloc(t->size, sizeof(int));
    int younger = get_youngest(&inverted_team, node, visited, __INT_MAX__, 1);
    if(younger == __INT_MAX__)
        return -1;
    else
        return younger;
}

//returns infinity if it doesn't have a commander
int get_youngest(team *t, int node, int *visited, int youngest, int original) {
    cell *p = t->adjacency[node].start->next;
    int new_youngest;
    visited[node] = GRAY;
    
    if(!original)
        youngest = t->ages[node] < youngest ? t->ages[node] : youngest;
    else
        original = 0;
   
    while (p != NULL) {
        if(visited[p->item] == WHITE) {
            new_youngest = get_youngest(t, p->item, visited, youngest, original);
            if(new_youngest < youngest)
                youngest = new_youngest;
        }
        p = p->next;
    }
    return youngest;
}