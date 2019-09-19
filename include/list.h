#ifndef LIST_H
#define LIST_H

struct _cell{
	int item;
	struct _cell *next;
};
typedef struct _cell cell;

typedef struct{
    cell *start;
    cell *end;
}list;

void make_empty_list(list *l);
int is_list_empty(list *l);
void add_item_start(list *l, int item);
void add_item_end(list *l, int item);
int remove_item_start(list *l);
int remove_item_end(list *l);
cell *find(list *l, int item);
void remove_by_item(list *l, int item);
void free_list(list *l);

#endif