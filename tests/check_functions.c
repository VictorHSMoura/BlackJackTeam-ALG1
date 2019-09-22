#include <check.h>
#include <stdlib.h>
#include "check_check.h"
#include "../include/functions.h"

#define N 7
#define M 8

team t;

void setup_functions(){
    int ages[N] = {21, 33, 34, 18, 42, 22, 26};
    int src[M] = {1, 1, 2, 3, 6, 4, 4, 6};
    int dest[M] = {2, 3, 5, 5, 3, 6, 7, 7};
    make_empty_team(&t, N);

    for(int i = 0; i < N; i++)
        set_age(&t, i, ages[i]);

    for(int i = 0; i < M; i++)
        insert_edge(&t, src[i], dest[i]);
}

START_TEST (test_meeting) {
    list l = meeting(&t);
    int desired[N] = {4, 6, 7, 1, 3, 2, 5};
    cell *p = l.start->next;

    for(int i = 0; i < N; i++, p = p->next){
        ck_assert_int_eq(desired[i], p->item);
    }
} END_TEST

START_TEST (test_verify_cycle) {
    ck_assert_int_eq(0, verify_cycle(&t));

    insert_edge(&t, 7, 4);
    ck_assert_int_eq(1, verify_cycle(&t));
} END_TEST

START_TEST (test_swap) {
    ck_assert_int_eq(1, swap(&t, 6, 3)); // valid swap
    ck_assert_ptr_eq(NULL, find(&t.adjacency[5], 2));
    ck_assert_ptr_ne(NULL, find(&t.adjacency[2], 5));

    ck_assert_int_eq(0, swap(&t, 4, 2)); // swap between nodes without an edge
    
    ck_assert_int_eq(0, swap(&t, 4, 7)); // swap that generates a cycle
    ck_assert_int_eq(0, swap(&t, 7, 4)); // checking in both directions
    ck_assert_ptr_eq(NULL, find(&t.adjacency[6], 3));
    ck_assert_ptr_ne(NULL, find(&t.adjacency[3], 6));
} END_TEST

START_TEST (test_invert_edges) {
    team inverted_team = invert_edges(&t);

    for(int i = 0; i < N; i++) {
        cell *p = t.adjacency[i].start->next;
        while (p != NULL) {
            //check if exists a node from the dest to the src on the inverted team
            ck_assert_ptr_ne(NULL, find(&inverted_team.adjacency[p->item], i));
            p = p->next;
        }
    }
    free_team(&inverted_team);
} END_TEST

START_TEST (test_get_younger) {
    int *visited = (int *) calloc(t.size, sizeof(int));
    ck_assert_int_eq(33, get_younger(&t, 0, visited, INFINITY));
    ck_assert_int_eq(26, get_younger(&t, 6, visited, INFINITY));
} END_TEST

START_TEST (test_commander) {
    ck_assert_int_eq(18, commander(&t, 2));
    ck_assert_int_eq(-1, commander(&t, 3));
} END_TEST

void end_functions() {
    free_team(&t);
}

Suite *functions_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Functions");

    /*Core test case*/
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup_functions, end_functions);
    tcase_add_test(tc_core, test_meeting);
    tcase_add_test(tc_core, test_verify_cycle);
    tcase_add_test(tc_core, test_swap);
    tcase_add_test(tc_core, test_invert_edges);
    tcase_add_test(tc_core, test_get_younger);
    tcase_add_test(tc_core, test_commander);
    suite_add_tcase(s, tc_core);

    return s;
}