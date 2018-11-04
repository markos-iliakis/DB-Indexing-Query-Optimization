#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "help_functions.h"
#include "result.h"

// #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
// #define mu_run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)
extern int tests_run;

void h1_test();
void hist_test();


static int test_makeHashIdArray(int **input_array, tuple *out, int length);
static int test_makeHistArray();
static int test_createPsum();
static int test_createReorderedarray();
static int test_createBucketIndexes();
static int test_createResults();