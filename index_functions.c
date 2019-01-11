#include "index_functions.h"

bucket_index** createBucketIndexes(sum** psum, int hist_length, ord_relation** rel){

    bucket_index** indexes = malloc(hist_length * sizeof(bucket_index *));

    int pos = 0;

    // for each bucket
    for (int i = 0; i < hist_length; i++) {


        int top = (i==0) ? 0 : psum[i-1]->index;
        int bottom = psum[i]->index-1;

        int bucket_size = bottom - top + 1;

        indexes[i] = malloc(sizeof(bucket_index));
        indexes[i]->chain = malloc((bucket_size) * sizeof(int));
        indexes[i]->bucket = malloc(101 * sizeof(int));

        // must initialize arrays to -1
        for(int y=0; y < 101; y++)
            indexes[i]->bucket[y] = -1;

        for(int y=0; y < bucket_size; y++)
            indexes[i]->chain[y] = 0;

        // printf("In bucket %3d Bottom : %3d top : %3d Pos : %2d\n",  i, bottom, top, pos);

        // for each element in the bucket(last->first)
        for(int j=bucket_size + pos - 1; j>=pos; j--){

            int element = h2(rel[j]->value);
            // printf("j : %3d H2 : %3d\n", j-pos, element);


            // store the last value of bucket[i] in bucket array accordind to the hash value
            if(indexes[i]->bucket[element] == -1){    /* first time case */
                // printf("Insert in bucket[%d] <- %d\n", element, j+1-pos);
                indexes[i]->bucket[element] = j+1-pos;
            }
            else{   /* regular case */
                int temp = indexes[i]->bucket[element];
                while(indexes[i]->chain[temp-1] != 0){
                    // printf("chain[%d] -> %d\n", temp, indexes[i]->chain[temp-1]);
                    // getchar();
                    temp = indexes[i]->chain[temp-1];
                }
                // printf("Insert in chain[%d] <- %d\n", temp, j+1-pos);
                indexes[i]->chain[temp-1] = j+1-pos;
            }
        }
        pos =  psum[i]->index;
        /* Bucket_tb and Chain hold the elements with the same hash(2) */
    }
    return indexes;
}


void printChains(bucket_index** buckets, int num_buckets, sum** psum){

    printf("---------------\n");
    printf("Chains\n");
    for(int i = 0; i < num_buckets; i++){

        int top = (i==0) ? 0 : psum[i-1]->index;
        int bottom = psum[i]->index-1;
        int bucket_size = bottom - top + 1;
        printChain(buckets[i]->chain, bucket_size);
    }
    printf("---------------\n");

}

void printChain(int* chain, int size){
    for(int j = 0; j < size; j++){
        printf("%d\n", chain[j]);
    }
    printf("---------------\n");
}

void destroyBucketIndexes(bucket_index** ind, int size){
    for(int i=0; i<size; i++){
        free(ind[i]->bucket);
        free(ind[i]->chain);
        free(ind[i]);
    }
    free(ind);
}

indexes_array* createIndexes(tb_array* tb){

    indexes_array* i_a = malloc(sizeof(indexes_array));
    i_a->ind = malloc(tb->size*sizeof(indexes*));

    // for every table
    // printf("Size : %d\n", tb->size);
    for(int i=0; i<tb->size; i++){

        i_a->ind[i] = malloc(tb->size * sizeof(indexes));
        i_a->ind[i]->array_relations = malloc(tb->tb[i]->colNum * sizeof(relation *));
        i_a->ind[i]->array_histograms = malloc(tb->tb[i]->colNum * sizeof(histogram *));
        i_a->ind[i]->ord_relations = malloc(tb->tb[i]->colNum * sizeof(ord_relation **));
        i_a->ind[i]->array_psums = malloc(tb->tb[i]->colNum * sizeof(sum **));
        i_a->ind[i]->array_bucket_indexes = malloc(tb->tb[i]->colNum * sizeof(bucket_index **));
        i_a->ind[i]->colNum = tb->tb[i]->colNum;

        // for every column

        for(int j=0; j<tb->tb[i]->colNum; j++){

            // printf("i : %d j: %d\n", i, j);
            i_a->ind[i]->array_relations[j] = malloc(tb->tb[i]->rowNum * sizeof(relation));

            // make the hashings from the starting relations
            i_a->ind[i]->array_relations[j]->tuples = makeHashIdArray(tb->tb[i]->col, tb->tb[i]->rowNum, j);
            i_a->ind[i]->array_relations[j]->num_tuples = tb->tb[i]->rowNum;
            // printTestColumnHashed(i_a->ind[i]->array_relations[j]->tuples, i_a->ind[i]->array_relations[j]->num_tuples);

            //find different values for x_tuple and create x_hist
            histArgs* hArg = histArgsInit(0, tb->tb[i]->rowNum, i_a->ind[i]->array_relations[j]);
            createHistogram(hArg);
            i_a->ind[i]->array_histograms[j] = hArg->hist;
            // i_a->ind[i]->array_histograms[j] = createParallelHistogram(tb->tb[i]->rowNum, i_a->ind[i]->array_relations[j]);
            // printHistogram(i_a->ind[i]->array_histograms[j]);

            //make psum tables
            int hist_length = histogramSize(i_a->ind[i]->array_histograms[j]);
            i_a->ind[i]->array_psums[j] = createPsum(hist_length, i_a->ind[i]->array_histograms[j]);

            // create x'
            i_a->ind[i]->ord_relations[j] = createReorderedarray(i_a->ind[i]->array_psums[j], hist_length, i_a->ind[i]->array_relations[j], tb->tb[i]->rowNum);
            // i_a->ind[i]->ord_relations[j] = createParallelReaorderedArray(i_a->ind[i]->array_psums[j], hist_length, i_a->ind[i]->array_relations[j], tb->tb[i]->rowNum);
            // printOrderedarray(i_a->ind[i]->ord_relations[j], tb->tb[i]->rowNum);

            // create indexes
            i_a->ind[i]->array_bucket_indexes[j] = createBucketIndexes(i_a->ind[i]->array_psums[j], hist_length, i_a->ind[i]->ord_relations[j]);

        }
    }
    return i_a;
}

void destroyIndexes(indexes_array* indexes){

    for(int i = 0; i < indexes->size; i++){
        for(int j = 0; j < indexes->ind[i]->colNum; j++){

            destroyOrdArray(indexes->ind[i]->ord_relations[j], indexes->ind[i]->array_relations[j]->num_tuples);
            int hist_length = histogramSize(indexes->ind[i]->array_histograms[j]);

            destroyBucketIndexes(indexes->ind[i]->array_bucket_indexes[j], hist_length);

            destroySum(indexes->ind[i]->array_psums[j], hist_length);

            destroyRelation(indexes->ind[i]->array_relations[j]);

            destroyHistogram(indexes->ind[i]->array_histograms[j]);
        }

        free(indexes->ind[i]->array_bucket_indexes);
        free(indexes->ind[i]->ord_relations);
        free(indexes->ind[i]->array_psums);
        free(indexes->ind[i]->array_relations);
        free(indexes->ind[i]->array_histograms);
        indexes->ind[i]->array_bucket_indexes = NULL;
        indexes->ind[i]->ord_relations = NULL;
        indexes->ind[i]->array_psums = NULL;
        indexes->ind[i]->array_relations = NULL;
        indexes->ind[i]->array_histograms = NULL;

    }

    free(indexes->ind);
    indexes->ind = NULL;

    free(indexes);
    indexes = NULL;
}
