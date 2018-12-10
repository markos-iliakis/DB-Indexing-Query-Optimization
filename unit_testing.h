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

void h1_test1();
void h1_test2();
void h1_test3();

void hist_test1();
void hist_test2();
void hist_test3();

void psum_test1();
void psum_test2();
void psum_test3();

void ord_test1();
void ord_test2();
void ord_test3();

void index_test1();
void index_test2();
void index_test3();

<<<<<<< HEAD
//void parseInput_test(void);

// void loadTables_test(void);

// void createIndexes_test(void);

// void parseInstructions_test(void);

// void makeInstructionsQueue_test(void);

// void executeQuery_test(void);

// void checkSum_test(void);

// void filterApplication_test(void);

// void joinValue_test(void);

// void selfJoin_test(void);

// void joinArrays_test(void);

// void addArray_test(void);

// void searchArray_test(void);
=======
void parseInput_test(void);

void loadTables_test(void);

void createIndexes_test(void);

void parseInstructions_test(void);

void makeInstructionsQueue_test(void);

void executeQuery_test(void);

void checkSum_test(void);

void filterApplication_test(void);

void joinValue_test(void);

void selfJoin_test(void);

void joinArrays_test(void);

void addArray_test(void);

void searchArray_test(void);
>>>>>>> 78fd968eadea9f8977a87f60a614fc1b588e7d64


static int test_makeHashIdArray(int64_t **input_array, tuple **out, int length);
static int test_makeHistArray(relation *, histogram *, int );
static int test_createPsum(int, histogram *, sum **);
static int test_createReorderedarray(sum **, int, ord_relation **, relation *, int );
static int test_createBucketIndexes(sum **, int, ord_relation **, bucket_index **);
// static int test_createResults(result *result_test, ord_relation **r_ord, ord_relation **s_ord, bucket_index **r_bucket_indexes, sum **r_psum, sum **s_psum, int r_hist_length, int s_hist_length) {
// static int test_parseInput(void);
// static int test_loadTables(void);
// static int test_createIndexes(void);
// static int test_parseInstructions(void);
// static int test_makeInstructionsQueue(void);
// static int test_executeQuery(void);
// static int test_checkSum(void);
// static int test_filterApplication(void);
// static int test_joinValue(void);
// static int test_selfJoin(void);
// static int test_joinArrays(void);
// static int test_addArray(void);
// static int test_searchArray(void);
