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

void destroyIndexes(bucket_index** ind, int size){
    for(int i=0; i<size; i++){
        free(ind[i]->bucket);
        free(ind[i]->chain);
        free(ind[i]);
    }
    free(ind);
}
