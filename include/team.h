#ifndef TEAM_H
#define TEAM_H

#include "list.h"
#define OFFSET 1

typedef struct {
    int *ages;
    list *adjacency;
    int size;
}team;

void make_empty_team(team *t, int size);
void set_age(team *t, int position, int age);
void insert_edge(team *t, int source, int dest);
void free_team(team *t);

#endif