#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "team.h"

list meeting(team *t);
void topological_order(team *t, int *visited, int node, list *l);
int swap(team *t, int src, int dest);
int verify_cycle(team *t);
int dfs_cycle(team *t, int *visited, int node);

#endif