#include "unit_testing.h"

#define ROWS 2

static int test_makeHashIdArray(int **input_array, tuple* out, int length){

    tuple *t = makeHashIdArray(input_array, length);

    for(int i = 0; i < length; i++){

        for (int j = 0; j < 3; j++) {
            printf("\n%d", input_array[i][j]);
        }
    }

    for(int i = 0; i < length; i++){
        // printf("\nt : %d\nout : %d\n", t[i].key, out[i].key);
        printf("key %3d\npayload : %3d\nvalue : %3d\n\n", t[i].key, t[i].payload, t[i].value);
    }
    for(int i = 0; i < length; i++){
        if(t[i].key != out[i].key) 
            return 0;
    }
    return 1;
}

static int test_makeHistArray(relation *hashed_check, histogram *hist_check, int length) {

    histogram* h = createHistogram(length, hashed_check);

    for(int i = 0; i < length; i++){
        if (h->value != hist_check->value)
            return 0;
        
        if (h->freq != hist_check->freq)
            return 0;

        h = h->next;
        hist_check = hist_check->next;
    }

    return 1;

}

static int test_createPsum(int hist_length, histogram* hist_check, sum* psum_check) {
    sum* psum = createPsum(hist_length, hist_check);

    for(int i=0; i < hist_length; i++){
        if(psum[i].hashed_key != psum_check[i].hashed_key || psum[i].index != psum_check[i].index) 
            return 0;
    }
    return 1;
}

static int test_createReorderedarray(sum *psum_check, int size, relation *hashed_check, int xdimen) {
    ord_relation*  ord_r = createReorderedarray(psum_check, size, hashed_check, xdimen);

    for (int i = 0; i < ) {

    }

}

static int test_createBucketIndexes(sum* psum, int length, ord_relation* rel) {
    bucket_index *bucket_test = createBucketIndexes(psum, length rel);

    for (int i = 0; i <) {

    }
}  

static int test_createResults() {

}

int init_suite(void) {
    return 0; 
}

int clean_suite(void) { 
    return 0; 
}

// static char* all_tests(){
//     return 0;
// }


void h1_test(void) {

    int **testing_array = malloc(2 * sizeof(int *));
    // tuple *hashed_array = malloc(2 * sizeof(tuple);

    for (int i = 0; i < ROWS; i++)
        testing_array[i] = malloc(3 * sizeof(int));

    testing_array[0][0] = 1;
    testing_array[0][1] = 2;
    testing_array[0][2] = 3;
    testing_array[1][0] = 4;
    testing_array[1][1] = 5;
    testing_array[1][2] = 6;

    relation *hashed_check = malloc(sizeof(relation));
    hashed_check->tuples = malloc(ROWS * sizeof(tuple));
    hashed_check->tuples[0].key = 11;
    hashed_check->tuples[0].payload = 1;
    hashed_check->tuples[0].value = 3;
    hashed_check->tuples[1].key = 110;
    hashed_check->tuples[1].payload = 2;
    hashed_check->tuples[1].value = 6;

    CU_ASSERT_EQUAL( test_makeHashIdArray(testing_array, hashed_check->tuples, ROWS), 1);

    for (int i = 0; i < ROWS; i++){
        free(testing_array[i]);
        free(hashed_check->tuples[i]);
    }
    free(testing_array);
    free(hashed_check);
}

void hist_test(void) {

    relation *hashed_check = malloc(sizeof(relation));
    hashed_check->tuples = malloc(ROWS * sizeof(tuple));
    hashed_check->tuples[0].key = 11;
    hashed_check->tuples[0].payload = 1;
    hashed_check->tuples[0].value = 3;
    hashed_check->tuples[1].key = 110;
    hashed_check->tuples[1].payload = 2;
    hashed_check->tuples[1].value = 6;

    histogram* h = createHistogram(XDIMEN, hashed_check);

    histogram hist_check[2];
    hist_check[0] = {
        .value = 10,
        .freq = 1,
        .next = NULL
    };
    hist_check[1] = {
        .value = 100,
        .freq = 1,
        .next = &b
    };

    CU_ASSERT_EQUAL( test_makeHistIdArray(h, hist_check, XDIMEN), 1);

    for (int i = 0; i < ROWS; i++)
        free(hashed_check->tuples[i]);
    free(hashed_check);
}

void psum_check(void) {
    sum psum_check[2];
    psum_check[0] = {
        .hashed_key = 10,
        .index = 0
    };
    psum_check[1] = {
        .hashed_key = 100,
        .index = 1
    };

    CU_ASSERT_EQUAL(test_createPsum(), 1);
}

void ord_test(sum *psum_check, int size, relation *hashed_check, int xdimen){
    ord_relation ord_check[2];
    ord_check[0] = {
        .row_id = 1,
        .value = 2
    };
    ord_check[1] = {
        .row_id = 2,
        .value = 4
    };

    CU_ASSERT_EQUAL(test_createReorderedarray(psum_check, size, hashed_check, xdimen), 1);
}

void index_test(sum* psum, int size, ord_relation* rel){
    sum psum_check[2];
    psum_check[0] = {
        .hashed_key = 10,
        .index = 0
    };
    psum_check[1] = {
        .hashed_key = 100,
        .index = 1
    };

    ord_relation ord_check[2];
    ord_check[0] = {
        .row_id = 1,
        .value = 2
    };
    ord_check[1] = {
        .row_id = 2,
        .value = 4
    };

    CU_ASSERT_EQUAL(test_createBucketIndexes(psum, size, rel), 1);
}

void results_test(void) {
    sum psum_check[2];
    psum_check[0] = {
        .hashed_key = 10,
        .index = 0
    };
    psum_check[1] = {
        .hashed_key = 100,
        .index = 1
    };

    ord_relation ord_check[2];
    ord_check[0] = {
        .row_id = 1,
        .value = 2
    };
    ord_check[1] = {
        .row_id = 2,
        .value = 4
    };

    CU_ASSERT_EQUAL(test_createResults(psum, length, rel), 1);
}

//*****************************************************************************************************************************//
//** TIS METABLHTES POU THELETE GIA TA TESTS THA TIS FTIAKSETE MESA STO TEST AKOLOUTHISTE TH MORFH TOU h1_test OXI STH MAIN **//
//**************************************************************************************************************************//


int main(){

    CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
    if ( CUE_SUCCESS != CU_initialize_registry() )
        return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "max_test_suite", init_suite, clean_suite );
    if ( NULL == pSuite ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // char *result = all_tests();

    if (NULL == CU_add_test(pSuite, "h1_test", h1_test)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");


    CU_cleanup_registry();
   return CU_get_error();


    // if (result != 0) {
    //     printf("%s\n", result);
    // }
    // else {
    //     printf("ALL TESTS PASSED\n");
    // }
    // printf("Tests run: %d\n", tests_run);
}
