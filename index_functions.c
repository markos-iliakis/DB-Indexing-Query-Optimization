#include "index_functions.h"

bucket_index* createBucketIndexes(sum* psum, int hist_length, ord_relation* rel){

    bucket_index *indexes = malloc(hist_length * sizeof(bucket_index));

    // for each bucket
    for (size_t i = 0; i < hist_length; i++) {
        
        indexes[i].chain = malloc(psum[i].index*sizeof(int));
        indexes[i].bucket = malloc(101*sizeof(int));
        
        // must initialize arrays to -1
        for(int y=0; y<101; y++) indexes[i].bucket[y] = -1;
        for(int y=0; y<psum[i].index; y++) indexes[i].chain[y] = -1;

        int top = (i==0)?0:psum[i-1].index;
        int bottom = psum[i].index-1;

        // for each element in the bucket(last->first)
        for(int j=bottom; j>=top; j--){
            int hashed = h2(rel[i*j].value);

            if(indexes[i].bucket[hashed] == -1){    /* first time case */
                indexes[i].bucket[hashed] = j+1;
            }
            else{   /* regular case */
                int temp = indexes[i].bucket[hashed];
                while(temp != -1){            
                    if(indexes[i].chain[temp-1] == -1){
                        indexes[i].chain[temp-1] = j+1;
                        break;
                    }
                    temp = indexes[i].chain[temp-1];
                }
            }
        }
        /* Bucket_tb and Chain hold the elements with the same hash(2) */
    }

    return indexes;
}
