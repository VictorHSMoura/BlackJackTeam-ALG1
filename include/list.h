#ifndef LIST_H
#define LIST_H

struct _cell{
	int age;
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
void free_list(list *l);

#endif