#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "result.h"

// #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
// #define mu_run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)
extern int tests_run;

void h1_test();
void hist_test();


static int test_makeHashIdArray(int **input_array, tuple **out, int length);
static int test_makeHistArray(relation *, histogram *, int );
static int test_createPsum(int, histogram *, sum **);
static int test_createReorderedarray(sum **, int, ord_relation **, relation *, int );
static int test_createBucketIndexes(sum **, int, ord_relation **, bucket_index **);
// static int test_createResults(result *result_test, ord_relation **r_ord, ord_relation **s_ord, bucket_index **r_bucket_indexes, sum **r_psum, sum **s_psum, int r_hist_length, int s_hist_length) {

