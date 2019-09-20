#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "team.h"

#define INFINITY 2147483647

list meeting(team *t);
void topological_order(team *t, int *visited, int node, list *l);
int swap(team *t, int src, int dest);
int verify_cycle(team *t);
int dfs_cycle(team *t, int *visited, int node);
team invert_edges(team *t);
int commander(team *t, int node);
int get_younger(team *t, int node, int *visited,int minAge);

#endif