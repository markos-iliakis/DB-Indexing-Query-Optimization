#include "index_functions.h"

bucket_index* createBucketIndexes(sum* psum, int hist_length, ord_relation* rel){

    bucket_index *indexes = malloc(hist_length * sizeof(bucket_index));

    int pos = 0;

    // for each bucket
    for (size_t i = 0; i < hist_length; i++) {


        int top = (i==0) ? 0 : psum[i-1].index;
        int bottom = psum[i].index-1;

        int bucket_size = bottom - top + 1;

        indexes[i].chain = malloc((bucket_size) * sizeof(int));
        indexes[i].bucket = malloc(101 * sizeof(int));

        // must initialize arrays to -1
        for(int y=0; y < 101; y++)
            indexes[i].bucket[y] = -1;

        for(int y=0; y < bucket_size; y++)
            indexes[i].chain[y] = -1;



        printf("Ston bucket %3ld Bottom : %3d top : %3d Pos : %2d\n",  i, bottom, top, pos);

        // for each element in the bucket(last->first)
        for(int j=bucket_size + pos; j>=pos; j--){

            printf("j : %3d H2 : %3d\n", j, h2(rel[j].value));


            // store the last value of bucket[i] in bucket array accordind to the hash value
            if(indexes[i].bucket[h2(rel[j].value)] == -1){    /* first time case */
                printf("Bazw ston bucket %d sth thesi %d\n", i, h2(rel[j].value));
                indexes[i].bucket[h2(rel[j].value)] = j+1;
            }
            else{   /* regular case */
                // int temp = indexes[i].bucket[];
                int old_chain_pos = h2(rel[j].value), new_chain_pos = h2(rel[j].value);
                printf("Ston bucket exw balei sth thesi %d\n", old_chain_pos);
                getchar();
                while(indexes[i].chain[new_chain_pos] != -1){
                    printf("Koitazw sth thesi %d\n", old_chain_pos);
                    getchar();
                    old_chain_pos = new_chain_pos;
                    new_chain_pos = indexes[i].chain[old_chain_pos];
                }
                indexes[i].chain[new_chain_pos] = j+1;
            }


        }
        pos +=  psum[i].index;
        /* Bucket_tb and Chain hold the elements with the same hash(2) */
    }

    return indexes;
}


void printBuckets(bucket_index *buckets, int num_buckets, sum *psum){


    for(int i = 0; i < num_buckets; i++){

        int top = (i==0) ? 0 : psum[i-1].index;
        int bottom = psum[i].index-1;
        int bucket_size = bottom - top + 1;
        printf("Chain : %d Mhkos : %d\n", i, bucket_size);
        for(int j = 0; j < bucket_size; j++){
            printf("%d\n", buckets[i].chain[j]);
        }

    }

}
