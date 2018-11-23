#include "result.h"

int main(int argc, char** argv){

    srand(time(NULL));

    // check input
    if(argv[1] == NULL){
        perror("wrong arguments\n");
        exit(-1);
    }

    // make the random arrays
    int** r_array = makeRandArray(XDIMEN, YDIMEN);
    int** s_array = makeRandArray(XDIMEN, YDIMEN);

    // make the id/hashed-value arrays
    relation* r_relation = malloc(sizeof(relation));
    relation* s_relation = malloc(sizeof(relation));

    /* get relations from the paths written in the file
    on the path described from the first argument */
    relation** rels = loadRelations(argv[1]);

    // make the hashings from the starting relations
    r_relation->tuples = makeHashIdArray(r_array, XDIMEN);
    r_relation->num_tuples = XDIMEN;
    s_relation->tuples = makeHashIdArray(s_array, XDIMEN);
    s_relation->num_tuples = XDIMEN;
    
    //print arrays
    // printArrayTuple(r_array, r_relation->tuples, XDIMEN, YDIMEN);
    // printArrayTuple(s_array, s_relation->tuples, XDIMEN, YDIMEN);

    //find different values for x_tuple and create x_hist
    histogram* r_hist = createHistogram(XDIMEN ,r_relation);
    histogram* s_hist = createHistogram(XDIMEN ,s_relation);

    //print r_histogram
    // printHistogram(r_hist);

    //make psum tables
    int r_hist_length = histogramSize(r_hist), s_hist_length = histogramSize(s_hist);
    sum** r_psum = createPsum(r_hist_length, r_hist);
    sum** s_psum = createPsum(s_hist_length, s_hist);

    // print psum table
    // printPsum(r_psum, r_hist_length);

    // create r'-s'
    ord_relation** r_ord = createReorderedarray(r_psum, r_hist_length, r_relation, XDIMEN);
    ord_relation** s_ord = createReorderedarray(s_psum, s_hist_length, s_relation, XDIMEN);

    // print r'
    printOrderedarray(r_ord);
    printOrderedarray(s_ord);

    // create indexes
    bucket_index** r_bucket_indexes = createBucketIndexes(r_psum, r_hist_length, r_ord);

    // print the indexing chains
    // printChains(r_bucket_indexes, r_hist_length, r_psum);

    result *join_result = RadixHashJoin(r_ord, s_ord, r_bucket_indexes, r_psum, s_psum, r_hist_length, s_hist_length);
    
    // print the RadixHash results
    printResults(join_result);

    destroyResult(join_result);

    destroyIndexes(r_bucket_indexes, r_hist_length);
    destroyOrdArray(r_ord, XDIMEN);
    destroyOrdArray(s_ord, XDIMEN);

    destroySum(r_psum, r_hist_length);
    destroySum(s_psum, s_hist_length);

    destroyRelation(r_relation);
    destroyRelation(s_relation);

    destroyRandArray(r_array, XDIMEN);
    destroyRandArray(s_array, XDIMEN);

    destroyHistogram(r_hist);
    destroyHistogram(s_hist);

    //more destroys

    return 0;
}
