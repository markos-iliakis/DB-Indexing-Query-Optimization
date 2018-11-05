#include "result.h"

result* createBuffer(result *prev) {
    result *new = malloc(sizeof(result));
    new->buffer = malloc(128 * sizeof(int32_t *));

    for(int i = 0; i < 128; i++) {
        new->buffer[i] = malloc(2 * sizeof(int32_t));
        new->buffer[i][0] = -1;
        new->buffer[i][1] = -1;
    }            

    new->next = NULL;

    if (prev != NULL)    
        prev->next  = new;

    return new;                            
}

result* RadixHashJoin(ord_relation *relR, ord_relation *relS, bucket_index *r_bucket_indexes, sum *r_psum, sum *s_psum, int r_hist_length, int s_hist_length){
    
    result *root = createBuffer(NULL);
    result *current_buffer = root;

    int buffer_pos = 0;

    for(int i = 0; i < s_hist_length; i++) {

        // The hash value we want to check from each bucket of S
        int hash_to_check = s_psum[i].hashed_key;

        for (int j = 0; j < r_hist_length; j++) {

            if (r_psum[j].hashed_key == hash_to_check) {

                // Find the rows of bucket in R
                int start = (i==0) ? 0 : s_psum[i-1].index;
                int end = s_psum[i].index;

                // printf("End : %d Start : %d\n", end, start);

                // for each row of bucket
                for (int k = start; k < end; k++) {

                    int32_t to_check = relS[k].value;
                    int test = r_bucket_indexes[j].bucket[h2(to_check)];

                    while (test > 0) {
                        // printf("Test : %d\n", test);
                          //sth thesh 0 tou buffer row id apo ton R kai sth thesh 1 row id apo ton S
                        if (relR[test-1].value == to_check) {

                            //If there is space in buffer
                            if(buffer_pos < 127){
                                current_buffer->buffer[buffer_pos][0] = relR[test-1].row_id;
                                current_buffer->buffer[buffer_pos][1] = relS[k].row_id;
                                buffer_pos++;
                            }
                            //Not enough space in current buffer create new node
                            else{
                                result *new_buffer = createBuffer(current_buffer);
                                new_buffer->buffer[0][0] = relR[test-1].row_id;
                                new_buffer->buffer[0][1] = relS[k].row_id;
                                buffer_pos = 1;
                                current_buffer = new_buffer;
                            }
                        }
                        test = r_bucket_indexes[j].chain[test-1];
                    }
                }
            }
        }
    }

    return root;
    
}

void printResults(result *root) {
    
    result *temp = root;
    int i;
    FILE *f = fopen("res.txt", "w");
    fprintf(f, "R       |       S\n----------------------------------\n");
    while (temp != NULL) {
        i = 0;
        while (temp->buffer[i][0] != -1) {
            fprintf(f, "%d              %d\n-------------------------------\n", temp->buffer[i][0], temp->buffer[i][1]);
            i++;
        }
        temp = temp->next;                                                                   
    }
    return; 
}

void destroyResult(result* r){
    result *temp = r;
   
    while (temp != NULL) {
        r = r->next;
        for(int i = 0; i < 128; i++) {
            free(temp->buffer[i]);
        }
        free(temp->buffer);
        free(temp);
        temp = r;                                                                   
    }
}