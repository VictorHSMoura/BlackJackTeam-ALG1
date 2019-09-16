#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "check_check.h"

int main(){
    int number_failed;
    SRunner *sr;

    sr = srunner_create(list_suite());
    srunner_add_suite(sr, team_suite());

    srunner_run_all(sr, CK_FAILURE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}