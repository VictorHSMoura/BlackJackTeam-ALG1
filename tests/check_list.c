#include <check.h>
#include <stdlib.h>
#include "check_check.h"
#include "../include/list.h"

static list l;

void setup_list(){
    make_empty_list(&l);
}

START_TEST (test_list_creation) {
    ck_assert_ptr_eq(l.start, l.end);
} END_TEST

START_TEST (test_add_item_start) {
    add_item_start(&l, 4);
    ck_assert_int_eq(4, l.start->next->item);

    add_item_start(&l, 8);
    ck_assert_int_eq(8, l.start->next->item);
} END_TEST

START_TEST (test_add_item_end) {
    add_item_end(&l, 4);
    ck_assert_int_eq(4, l.end->item);

    add_item_end(&l, 2);
    ck_assert_int_eq(2, l.end->item);
} END_TEST

START_TEST (test_remove_item_start) {
    add_item_start(&l, 4);
    add_item_start(&l, 7);
    ck_assert_int_eq(1, remove_item_start(&l));
    ck_assert_int_eq(4, l.start->next->item);
    ck_assert_int_eq(1, remove_item_start(&l));
    ck_assert_int_eq(0, remove_item_start(&l)); // not possible. Empty list
} END_TEST

START_TEST (test_remove_item_end) {
    add_item_start(&l, 4);
    add_item_start(&l, 7);
    add_item_start(&l, 9);
    ck_assert_int_eq(1, remove_item_end(&l));
    ck_assert_int_eq(7, l.end->item);
    ck_assert_int_eq(1, remove_item_end(&l));
    ck_assert_int_eq(9, l.end->item);
    ck_assert_int_eq(1, remove_item_end(&l));
    ck_assert_int_eq(0, remove_item_end(&l)); // not possible. Empty list
} END_TEST

START_TEST (test_list_empty) {
    ck_assert_int_eq(1, is_list_empty(&l));

    add_item_start(&l, 4);
    ck_assert_int_eq(0, is_list_empty(&l));
    remove_item_start(&l);
    ck_assert_int_eq(1, is_list_empty(&l));
} END_TEST

START_TEST (test_list_find) {
    for (int i = 1; i <= 5; i++)
        add_item_end(&l, i);
    ck_assert_ptr_ne(NULL, find(&l, 3));
    ck_assert_ptr_eq(NULL, find(&l, 6));
} END_TEST

START_TEST (test_list_remove_by_pointer) {
    for (int i = 1; i <= 5; i++)
        add_item_end(&l, i);
    
    cell *item3 = find(&l, 3);
    ck_assert_ptr_ne(NULL, item3);
    remove_by_pointer(&l, item3);
    ck_assert_ptr_eq(NULL, find(&l, 3));
} END_TEST

START_TEST (test_add_item_by_pointer) {
    for (int i = 1; i <= 5; i++)
        add_item_end(&l, i);

    cell *item_before_3 = find(&l, 3);
    add_item_by_pointer(&l, item_before_3, 9);

    cell *p = l.start->next;
    int items[6] = {1, 2, 9, 3, 4, 5};
    for(int i = 0; i < 6; i++, p = p->next){
        ck_assert_int_eq(items[i], p->item);
    }
} END_TEST

void end_list(){
    free_list(&l);
}

Suite *list_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("List");

    /*Core test case*/
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup_list, end_list);
    tcase_add_test(tc_core, test_list_creation);
    tcase_add_test(tc_core, test_add_item_start);
    tcase_add_test(tc_core, test_add_item_end);
    tcase_add_test(tc_core, test_remove_item_start);
    tcase_add_test(tc_core, test_remove_item_end);
    tcase_add_test(tc_core, test_list_empty);
    tcase_add_test(tc_core, test_list_find);
    tcase_add_test(tc_core, test_list_remove_by_pointer);
    tcase_add_test(tc_core, test_add_item_by_pointer);
    suite_add_tcase(s, tc_core);

    return s;
}