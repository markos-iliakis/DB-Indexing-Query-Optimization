#include "unit_testing.h"

#define ROWS 2

static int test_makeHashIdArray(int **input_array, tuple** out, int length){

    relation *t = malloc(sizeof(relation));
    t->tuples = makeHashIdArray(input_array, length);

    for(int i = 0; i < length; i++){
        if(t->tuples[i]->key != out[i]->key)
            return 0;
    }
    //destroyRelation(t);
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
    // destroyHistogram(h);
    return 1;

}

static int test_createPsum(int hist_length, histogram* hist_check, sum** psum_check) {
    sum **psum = createPsum(hist_length, hist_check);

    for(int i=0; i < hist_length; i++){
        if(psum[i]->hashed_key != psum_check[i]->hashed_key || psum[i]->index != psum_check[i]->index)
            return 0;
    }
    //destroySum(psum);
    return 1;
}

static int test_createReorderedarray(sum **psum_check, int size, ord_relation **ord_check, relation *hashed_check, int xdimen) {
    ord_relation **ord_r = createReorderedarray(psum_check, size, hashed_check, xdimen);

    for (int i = 0; i < xdimen; i++) {
        if (ord_r[i]->value != ord_check[i]->value)
            return 0;

        if (ord_r[i]->row_id != ord_check[i]->row_id)
            return 0;
    }
    //destroyOrdArray(ord_r);
    return 1;
}

static int test_createBucketIndexes(sum** psum, int length, ord_relation** rel, bucket_index **test_indexes) {
    bucket_index **bucket_test = createBucketIndexes(psum, length, rel);

    for (int i = 0; i < length; i++) {
        // check of bucket array
        for (int j = 0; j < 101; j++)
            if(bucket_test[i]->bucket[j] != test_indexes[i]->bucket[j])
                return 0;

        int top = (i==0) ? 0 : psum[i-1]->index;
        int bottom = psum[i]->index-1;

        int bucket_size = bottom - top + 1;

        // check of chain
        for (int j = 0; j < bucket_size; j++)
            if(bucket_test[i]->chain[j] != test_indexes[i]->chain[j])
                return 0;
     }

    // destroyIndexes(bucket_test, length);
    return 1;
}


int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}


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
    for (int i = 0; i < ROWS; i++)
        hashed_check->tuples[i] = malloc(sizeof(tuple));
    hashed_check->tuples[0]->key = 11;
    hashed_check->tuples[0]->payload = 1;
    hashed_check->tuples[0]->value = 3;
    hashed_check->tuples[1]->key = 110;
    hashed_check->tuples[1]->payload = 2;
    hashed_check->tuples[1]->value = 6;
    
    CU_ASSERT_EQUAL( test_makeHashIdArray(testing_array, hashed_check->tuples, ROWS), 1);

    // for (int i = 0; i < ROWS; i++){
    //     free(testing_array[i]);
    // }
    // free(hashed_check->tuples);
    // free(testing_array);
    // free(hashed_check);
}

void hist_test(void) {

    relation *hashed_check = malloc(sizeof(relation));
    hashed_check->tuples = malloc(ROWS * sizeof(tuple));
    for (int i = 0; i < ROWS; i++)
        hashed_check->tuples[i] = malloc(sizeof(tuple));
    hashed_check->tuples[0]->key = 11;
    hashed_check->tuples[0]->payload = 1;
    hashed_check->tuples[0]->value = 3;
    hashed_check->tuples[1]->key = 110;
    hashed_check->tuples[1]->payload = 2;
    hashed_check->tuples[1]->value = 6;
    
    histogram* h = createHistogram(2, hashed_check);
    
    histogram *node1 = malloc(sizeof(histogram));
    histogram *node2 = malloc(sizeof(histogram));
    
    node1->value = 11;
    node1->freq = 1;
    node1->next = node2;

    node2->value = 110;
    node2->freq = 1;
    node2->next = NULL;
    
    CU_ASSERT_EQUAL( test_makeHistArray(hashed_check, node1, 2), 1);


    // free(hashed_check->tuples);
    // free(hashed_check);
    // free(node1);
    // free(node2);
}

void psum_test(void) {

    sum **psum_check = malloc(2*sizeof(sum));
    for (int i = 0; i < 2; i++)
        psum_check[i] = malloc(sizeof(**psum_check));
    psum_check[0]->hashed_key = 11;
    psum_check[0]->index = 0;
    psum_check[1]->hashed_key = 110;
    psum_check[1]->index = 1;

    histogram *node1 = malloc(sizeof(histogram));
    histogram *node2 = malloc(sizeof(histogram));
    node1->value = 11;
    node1->freq = 1;
    node1->next = node2;

    node2->value = 110;
    node2->freq = 1;
    node2->next = NULL;
    
    CU_ASSERT_EQUAL(test_createPsum(2, node1, psum_check), 1);

    // free(node1);
    // free(node2);
    // free(psum_check);
}

void ord_test(void){

    relation *hashed_check = malloc(sizeof(relation));
    hashed_check->tuples = malloc(ROWS * sizeof(tuple));
    for (int i = 0; i < ROWS; i++)
        hashed_check->tuples[i] = malloc(sizeof(tuple));
    hashed_check->tuples[0]->key = 11;
    hashed_check->tuples[0]->payload = 1;
    hashed_check->tuples[0]->value = 3;
    hashed_check->tuples[1]->key = 110;
    hashed_check->tuples[1]->payload = 2;
    hashed_check->tuples[1]->value = 6;

    ord_relation **ord_check = malloc(2*sizeof(ord_relation));
    for (int i = 0; i < 2; i++) {
        ord_check[i] = malloc(sizeof(ord_relation));
    }
    ord_check[0]->row_id = 1;
    ord_check[0]->value = 3;
    ord_check[1]->row_id = 2;
    ord_check[1]->value = 6;

    sum **psum_check = malloc(2*sizeof(sum));
    for (int i = 0; i < 2; i++)
        psum_check[i] = malloc(sizeof(**psum_check));
    psum_check[0]->hashed_key = 11;
    psum_check[0]->index = 0;
    psum_check[1]->hashed_key = 110;
    psum_check[1]->index = 1;

    CU_ASSERT_EQUAL(test_createReorderedarray(psum_check, 2, ord_check, hashed_check, 2), 1);

    // destroyOrdArray(ord_check);
    // free(hashed_check->tuples);
    // free(hashed_check);
    // free(ord_check);
    // destroySum(psum_check);
}

void index_test(void){

    ord_relation **ord_rel = malloc(6 * sizeof(ord_relation));
    for (int i = 0; i < 6; i++) {
        ord_rel[i] = malloc(sizeof(ord_relation));
    }
    ord_rel[0]->row_id = 1;
    ord_rel[0]->value = 3;
    ord_rel[1]->row_id = 2;
    ord_rel[1]->value = 3;
    ord_rel[2]->row_id = 3;
    ord_rel[2]->value = 3;
    ord_rel[3]->row_id = 4;
    ord_rel[3]->value = 6;
    ord_rel[4]->row_id = 5;
    ord_rel[4]->value = 6;
    ord_rel[5]->row_id = 6;
    ord_rel[5]->value = 6;

    sum **psum_check = malloc(2 * sizeof(sum));
    for (int i = 0; i < 2; i++)
        psum_check[i] = malloc(sizeof(**psum_check));
    psum_check[0]->hashed_key = 11;
    psum_check[0]->index = 3;
    psum_check[1]->hashed_key = 110;
    psum_check[1]->index = 6;

    bucket_index **test_indexes = malloc(2 * sizeof(bucket_index));
    for (int i = 0; i < 2; i++) {

        int top = (i==0) ? 0 : psum_check[i-1]->index;
        int bottom = psum_check[i]->index-1;

        int bucket_size = bottom - top + 1;
        
        test_indexes[i] = malloc(sizeof(bucket_index));
        test_indexes[i]->chain = malloc((bucket_size) * sizeof(int));
        test_indexes[i]->bucket = malloc(101 * sizeof(int));

        for(int y=0; y < 101; y++)
            test_indexes[i]->bucket[y] = -1;

        for(int y=0; y <= bucket_size; y++)
            test_indexes[i]->chain[y] = 0;
    }
    printf("hi\n");
    test_indexes[0]->bucket[h2(ord_rel[2]->value)] = 3;
    test_indexes[1]->bucket[h2(ord_rel[5]->value)] = 3;

    test_indexes[0]->chain[2] = 2;
    test_indexes[0]->chain[1] = 1;

    test_indexes[1]->chain[2] = 2;
    test_indexes[1]->chain[1] = 1;




    CU_ASSERT_EQUAL(test_createBucketIndexes(psum_check, 2, ord_rel, test_indexes), 1);

    // for (int i = 0; i < 2; i++) {
    //     free(test_indexes[i]->chain);
    //     free(test_indexes[i]->bucket);
    // }

    // // destroyOrdArray(ord_rel);
    // destroySum(psum_check);
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
   pSuite = CU_add_suite( "part_1_suite", init_suite, clean_suite );
    if ( NULL == pSuite ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "h1_test", h1_test)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "hist_test", hist_test)) {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "psum_test", psum_test)) {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "ord_test", ord_test)) {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "index_test", index_test)) {
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
