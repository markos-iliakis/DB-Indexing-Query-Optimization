#include "index_functions.h"

bucket_index* createBucketIndexes(sum* psum, int hist_length, ord_relation* rel){

    bucket_index *indexes = malloc(hist_length * sizeof(bucket_index));

    // for each bucket
    for (size_t i = 0; i < hist_length; i++) {
        indexes[i].chain = malloc(psum[i]*sizeof(int));
        indexes[i].bucket = malloc(101*sizeof(int));
    }



    return indexes;
}
