#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "relation.h"
#include "help_functions.h"

// #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
// #define mu_run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)
extern int tests_run;

static int test_makeHashIdArray(int **input_array, tuple *out, int length);
void h1_test(int** array1, tuple* array2, int ROWS);
