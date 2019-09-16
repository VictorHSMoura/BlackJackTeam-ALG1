#ifndef TEAM_H
#define TEAM_H

#include "list.h"

typedef struct {
    int *ages;
    list *adjacency;
}team;

void make_empty_team(team *t, int size);
void set_age(team *t, int position, int age);
void insert_edge(team *t, int source, int dest);

#endif