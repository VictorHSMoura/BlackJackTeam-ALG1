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

team invert_edges(team *t) {
    team inverted_team;
    make_empty_team(&inverted_team, t->size);

    for(int i = 0; i < t->size; i++) {
        list edges = t->adjacency[i];
        for (cell *p = edges.start->next; p != NULL; p = p->next) {
            insert_edge(&inverted_team, p->item, i);
        }
        set_age(&inverted_team, i, t->ages[i]);
    }
    return inverted_team;
}

int commander(team *t, int node) {
    team inverted_team = invert_edges(t);
    int *visited = (int *) calloc(t->size, sizeof(int));
    int younger = get_younger(&inverted_team, node, visited, INFINITY);
    if(younger == inverted_team.ages[node])
        return -1;
    else
        return younger;
}

//returns node age if it doesn't have a commander
int get_younger(team *t, int node, int *visited, int minAge) {
    cell *p = t->adjacency[node].start->next;
    int younger = minAge;
    
    visited[node] = 1;
    if (p == NULL)
        return t->ages[node] < minAge? t->ages[node]: minAge;
    
    while (p != NULL) {
        if(visited[p->item] == 0){
            int new_age = get_younger(t, p->item, visited, t->ages[p->item]);
            if(new_age < younger)
                younger = new_age;
        }
        p = p->next;
    }
    return younger;
}