#include "unit_testing.h"

#define ROWS 2

static int test_makeHashIdArray(int **input_psum, int **checkout_psum, int length){
    
    for(int i = 0; i < length; i++){
        
    }
    
    return 1;
}

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }



static char* all_tests(){
    return 0;
}


void h1_test(int **array1, int **array2, int ROWS) {
  CU_ASSERT_EQUAL( test_makeHashIdArray(array1, array2, length), 1);
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
    int testing_array[2][2]={{1,2},{3,4}};
    int hashed_array[2][3]={{10, 1, 2}, {100, 2, 4}};


    if ( (NULL == CU_add_test(pSuite, "h1_test", h1_test(testing_array, hashed_array, ROWS)))) {
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

    int                     
    
    // if (result != 0) {
    //     printf("%s\n", result);
    // }
    // else {
    //     printf("ALL TESTS PASSED\n");
    // }
    // printf("Tests run: %d\n", tests_run);

    return 0;
}