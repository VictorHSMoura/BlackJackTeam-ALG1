#include <check.h>
#include "check_check.h"
#include "../include/team.h"

#define N 7

team t;

void setup(){
    make_empty_team(&t, N);
}

START_TEST (test_set_age) {
    set_age(&t, 0, 18);
    ck_assert_int_eq(18, t.ages[0]);

    set_age(&t, 4, 32);
    ck_assert_int_eq(32, t.ages[4]);
} END_TEST

START_TEST (test_insert_edge) {
    insert_edge(&t, 0, 2);
    ck_assert_int_eq(0, is_list_empty(&t.adjacency[0]));
    
    ck_assert_int_eq(1, is_list_empty(&t.adjacency[4]));
    insert_edge(&t, 4, 6);
    ck_assert_int_eq(0, is_list_empty(&t.adjacency[4]));
} END_TEST

void end_team() {
    free_team(&t);
}

Suite *team_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Team");

    /*Core test case*/
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, end_team);
    tcase_add_test(tc_core, test_set_age);
    tcase_add_test(tc_core, test_insert_edge);
    suite_add_tcase(s, tc_core);

    return s;
}