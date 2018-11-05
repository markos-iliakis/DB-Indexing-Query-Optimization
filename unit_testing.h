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

void h1_test(void);
void hist_test(void);
void psum_test(void);
void ord_test(void);
void index_test(void);
void results_test(void);


static int test_makeHashIdArray(int **input_array, tuple *out, int length);
static int test_makeHistArray(relation *, histogram *, int );
static int test_createPsum(int, histogram *, sum *);
static int test_createReorderedarray(sum *, int, ord_relation *, int );
static int test_createBucketIndexes(sum *, int, ord_relation *);
// static int test_createResults();