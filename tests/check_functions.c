#include <check.h>
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
        insert_edge(&t, src[i]-1, dest[i]-1);
}

START_TEST (test_meeting) {
    list l = meeting(&t);
    int desired[N] = {4, 6, 7, 1, 3, 2, 5};
    cell *p = l.start->next;

    for(int i = 0; i < N; i++, p = p->next){
        ck_assert_int_eq(desired[i], p->item + 1);
    }
} END_TEST

START_TEST (test_verify_cycle) {
    ck_assert_int_eq(0, verify_cycle(&t));

    insert_edge(&t, 6, 3); //7 4
    ck_assert_int_eq(1, verify_cycle(&t));
} END_TEST

START_TEST (test_swap) {
    ck_assert_int_eq(1, swap(&t, 5, 2)); // swap com sucesso
    ck_assert_ptr_eq(NULL, find(&t.adjacency[5], 2));
    ck_assert_ptr_ne(NULL, find(&t.adjacency[2], 5));

    ck_assert_int_eq(0, swap(&t, 3, 1)); // swap entre nós que não tem aresta
    
    ck_assert_int_eq(0, swap(&t, 3, 6)); // swap entre nós que geram ciclo
    ck_assert_ptr_eq(NULL, find(&t.adjacency[6], 3));
    ck_assert_ptr_ne(NULL, find(&t.adjacency[3], 6));
} END_TEST



void end_functions() {
    free_team(&t);
}

Suite *functions_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Team");

    /*Core test case*/
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup_functions, end_functions);
    tcase_add_test(tc_core, test_meeting);
    tcase_add_test(tc_core, test_verify_cycle);
    tcase_add_test(tc_core, test_swap);
    suite_add_tcase(s, tc_core);

    return s;
}