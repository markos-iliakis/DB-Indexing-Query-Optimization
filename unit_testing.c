#include "unit_testing.h"

static char* test_makeHashIdArray(){
    mu_assert("error, ", makeHashIdArray(r_array, XDIMEN););
    return 0;
}

static char* all_tests(){
    mu_run_test();
    return 0;
}

int main(){

    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}