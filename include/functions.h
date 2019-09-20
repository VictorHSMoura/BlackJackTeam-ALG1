#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "team.h"

list meeting(team *t);
void topological_order(team *t, int *visited, int node, list *l);

#endif