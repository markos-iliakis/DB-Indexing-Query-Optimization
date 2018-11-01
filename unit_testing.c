#include "unit_testing.h"

#define ROWS 2

static int test_makeHashIdArray(int **input_array, tuple* out, int length){
    
    tuple* t = makeHashIdArray(input_array, length);
    for(int i = 0; i < length; i++){
        if(t[i].key != out[i].key) return 0;    
    }
    return 1;
}

static int test_makeHistArray(relation *hashed_check, histogram *hist_check, int length) {
    
    histogram* h = createHistogram(length, hashed_check);

    for(int i = 0; i < length; i++){
        
    }
    
    return 1;        
    
}

static int test_createPsum(int hist_length, histogram* hist_check, sum* psum_check) {
    sum* psum = createPsum(hist_length, hist_check);

    for(int i=0; i < hist_length; i++){
        if(psum[i].hashed_key != psum_check[i].hashed_key || psum[i].index != psum_check[i].index) return 0;
    }   
    return 1;
}

static int test_createReorderedarray(sum *psum_check, int size, relation *hashed_check, int xdimen) {
    ord_relation*  ord_r = createReorderedarray(psum_check, size, hashed_check, xdimen);
}

static int test_createBucketIndexes(sum* psum, int length, ord_relation* rel){

}

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }



static char* all_tests(){
    return 0;
}


void h1_test(int **array1, tuple* array2, int length) {
    CU_ASSERT_EQUAL( test_makeHashIdArray(array1, array2, length), 1);
}

void psum_test(int length, histogram* hist, sum* psum){
    CU_ASSERT_EQUAL(test_createPsum(length, hist, psum), 1);
}

void ord_test(sum *psum_check, int size, relation *hashed_check, int xdimen){
    CU_ASSERT_EQUAL(test_createReorderedarray(psum_check, size, hashed_check, xdimen), 1);
}

void index_test(sum* psum, int size, ord_relation* rel){
    CU_ASSERT_EQUAL(test_createBucketIndexes(psum, size, rel), 1);
}

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


    char *result = all_tests();
    int testing_array[2][2] = {{1,2},{3,4}};
    relation hashed_check = {
        .tuples = {{10, 1, 2}, {100, 2, 4}},
        .num_tuples = 2
    };
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


    if ( (NULL == CU_add_test(pSuite, "h1_test", h1_test(testing_array, hashed_check.tuples, ROWS)))) {
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

    return 0;
}