#include "../include/team.h"
#include <stdlib.h>

void make_empty_team(team *t, int size) {
    t->ages = (int *) calloc(size, sizeof(int));
    t->adjacency = (list *) malloc(size * sizeof(list));
    for (int i = 0; i < size; i++)
        make_empty_list(&t->adjacency[i]);
    t->size = size;
}

void set_age(team *t, int position, int age) {
    t->ages[position] = age;
}

void insert_edge(team *t, int source, int dest) {
    add_item_end(&t->adjacency[source - OFFSET], dest - OFFSET);
}

void free_team(team *t) {
    free(t->ages);
    free_list(t->adjacency);
}