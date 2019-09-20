#include "../include/list.h"
#include <stdlib.h>
#include <stdio.h>

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
    l->start->item = item;
    new_cell->next = l->start;
    l->start = new_cell;
}

void add_item_end(list *l, int item) {
    l->end->next = (cell *) malloc(sizeof(cell));
    l->end = l->end->next;
    l->end->item = item;
    l->end->next = NULL;
}

void add_item_by_pointer(list *l, cell *item_before, int item) {
    cell *new_item = (cell *) malloc(sizeof(cell));
    new_item->item = item;
    new_item->next = item_before->next;
    item_before->next = new_item;

    if(item_before == l->end)
        l->end = new_item;
}

int remove_item_start(list *l) {
    if (is_list_empty(l))
        return 0;

    cell *p = l->start;
    l->start = l->start->next;
    free(p);
    return 1;
}

int remove_item_end(list *l) {
    if (is_list_empty(l))
        return 0;

    cell *p = l->start;
    while(p->next != l->end){
        p = p->next;
    }
    l->end = p;
    p = p->next;
    free(p);
    l->end->next = NULL;
    
    return 1;
}

//returns the pointer to 1 cell before the item
//if it don't exists, returns NULL
cell *find(list *l, int item) {
    cell *p = l->start;
    while (p->next != NULL) {
        if (p->next->item == item)
            return p;
        p = p->next;
    }
    return NULL;
}

void remove_by_pointer(list *l, cell *item_before){  
    if (item_before != NULL) {
        cell *item = item_before->next;
        if (item == l->end)
            l->end = item_before;
            
        item_before->next = item->next;
        free(item);
    }
}

void print_list(list *l) {
    cell *p = l->start->next;

    while (p != NULL) {
        printf("%d ", p->item + 1);
        p = p->next;
    }
    printf("\n");
}

void free_list(list *l) {
    cell *p = l->start;

    while (p != NULL) {
        l->start = p->next;
        free(p);
        p = l->start;
    }
}