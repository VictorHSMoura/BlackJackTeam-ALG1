#include "../include/list.h"
#include <stdlib.h>

void make_empty_list(list *l) {
    l->start = (cell *) malloc(sizeof(cell));
    l->end = l->start;
    l->start->next = NULL;
}

int is_list_empty(list *l) {
    return (l->start == l->end);
}

void add_item_start(list *l, int item) {
    cell *new_cell;
    new_cell = (cell *) malloc(sizeof(cell));
    l->start->age = item;
    new_cell->next = l->start;
    l->start = new_cell;
}

void add_item_end(list *l, int item) {
    l->end->next = (cell *) malloc(sizeof(cell));
    l->end = l->end->next;
    l->end->age = item;
    l->end->next = NULL;
}

int remove_item_start(list *l) {
    if (is_list_empty(l))
        return 0;

    cell *p = l->start;
    l->start = l->start->next;
    free(p);
    return 1;
}

void free_list(list *l) {
    cell *p = l->start;

    while (p != NULL) {
        l->start = p->next;
        free(p);
        p = l->start;
    }
}