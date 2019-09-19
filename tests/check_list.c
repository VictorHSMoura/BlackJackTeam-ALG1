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

START_TEST (test_list_remove_by_item) {
    for (int i = 1; i <= 5; i++)
        add_item_end(&l, i);
    
    ck_assert_ptr_ne(NULL, find(&l, 3));
    remove_by_item(&l, 3);
    ck_assert_ptr_eq(NULL, find(&l, 3));
} END_TEST

Suite *list_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("List");

    /*Core test case*/
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup_list, NULL);
    tcase_add_test(tc_core, test_list_creation);
    tcase_add_test(tc_core, test_add_item_start);
    tcase_add_test(tc_core, test_add_item_end);
    tcase_add_test(tc_core, test_remove_item_start);
    tcase_add_test(tc_core, test_list_empty);
    tcase_add_test(tc_core, test_list_find);
    tcase_add_test(tc_core, test_list_remove_by_item);
    suite_add_tcase(s, tc_core);

    return s;
}