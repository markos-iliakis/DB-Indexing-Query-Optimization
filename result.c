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

        int h1_value = h1(relS[pos].value);

        int psum_row_pos = searchPsum(int r_hist_length, r_psum, h1_value);

        if(psum_row_pos != -1){

            // find bucket area in r'
            int start, stop;
            if(psum_row_pos == 0){
                start = 0;
                stop = r_psum[psum_row_pos].index - 1;
            }
            else{
                start = r_psum[psum_row_pos - 1].index;
                stop = r_psum[psum_row_pos].index - 1;
            }
            int r_bucket_pos = start;

            // for each row of bucket of s
             for(int j = pos; j < bucket_size - 1; j++) {
            
                //tha paroume thn timh h2 gia thn timh mesa sto bucket
                if(r_bucket_indexes[psum_row_pos].bucket[h2(relS[pos].value)] != -1){

                    //shmainei oti exei brei timh h opoia h thesh ths einai apothikeumenh mesa sto bucket[]
                    
                    while(){

                    }
 
                    relR[r_bucket_pos]
                }
                    
                //
            }

            pos += bucket_size;
        }

        
    }

}