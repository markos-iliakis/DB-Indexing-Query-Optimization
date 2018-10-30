#include "result.h"


result* RadixHashJoin(ord_relation *relR, ord_relation *relS, bucket_index *r_bucket_indexes, sum *r_psum, sum *s_psum, int r_hist_length, int s_hist_length){
    
    result *root = malloc(sizeof(result));
    root->buffer = malloc(128 * sizeof(int32_t *));
    for(int i = 0; i < 128; i++)
        root->buffer[i] = malloc(2 * sizeof(int32_t));
    
    int pos = 0;

    //for every bucket of s
    for(int i = 0; i < s_hist_length; i++) {

        int top = (i==0) ? 0 : psum[i-1].index;
        int bottom = psum[i].index-1;
        int bucket_size = bottom - top + 1

        // for each row of bucket
        for(int j = pos; j < bucket_size - 1; j++) {
            
            //tha paroume thn timh h2 gia thn timh mesa sto bucket
            if()
                h2();
            //
        }

        pos += bucket_size;
    }

    r_bucket_indexes 

}