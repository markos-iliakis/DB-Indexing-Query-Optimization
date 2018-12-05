#include "result.h"

// edw isws thelei na einai dunamiko oi sthles tou buffer analoga me to posoi pinakes emplekontai
result* createBuffer(result *prev, int buffer_size) {
    result *new = malloc(sizeof(result));
    new->buffer = malloc((1024 / (buffer_size * sizeof(int32_t))) * sizeof(int32_t *));
    new->buffer_size = buffer_size;

    for(int i = 0; i < (1024 / (buffer_size * sizeof(int32_t))); i++) {
        new->buffer[i] = malloc(buffer_size * sizeof(int32_t));
        for (size_t j = 0; j < buffer_size; j++)
            new->buffer[i][j] = -1;
    }

    new->next = NULL;

    if (prev != NULL)
        prev->next  = new;

    return new;
}

void executeQuery(Queue* q){
    //estw edw oti exome to priority queue
    //ekteloume bhma bhma ta nodes pou einai mesa sthn priority queue
    query_metadata *metadata = NULL;

    for(int i=q->front; i< q->rear; i++){

        //exw filtro 
        if(q->array[i]->){
            //na ftiaksoume sunarthsh na efarmozei filtro kai na epostrefei result *            
        }

        //exw join        
        if(){
            
            //edw h radix
        }                    
    }
    //to teliko reuslt pou exei bgei bgazoume cheksum
}

// na balw orisma result* pou tha einai ta endiamesa apotelesmeta kai an den einai NULL kai pinakas pou thelw na kanw join exei ksanaginei join na xrhsimopoiw ta endiamea
result* RadixHashJoin(query_metadata **metadata, result *res, ord_relation **relR, ord_relation **relS, bucket_index **r_bucket_indexes, sum **r_psum, sum **s_psum, int r_hist_length, int s_hist_length, relation *relA){

    if(res == NULL){

        result *root = createBuffer(NULL, 2);
        result *current_buffer = root;

        int buffer_pos = 0;

        for(int i = 0; i < s_hist_length; i++) {

            // The hash value we want to check from each bucket of S
            int hash_to_check = s_psum[i]->hashed_key;

            for (int j = 0; j < r_hist_length; j++) {

                if (r_psum[j]->hashed_key == hash_to_check) {

                    // Find the rows of bucket in R
                    int start = (i==0) ? 0 : s_psum[i-1]->index;
                    int end = s_psum[i]->index;

                    // printf("End : %d Start : %d\n", end, start);

                    // for each row of  each bucket of S
                    for (int k = start; k < end; k++) {

                        int32_t to_check = relS[k]->value;
                        int test = r_bucket_indexes[j]->bucket[h2(to_check)];

                        while (test > 0) {

                            // printf("Test : %d to_check :  %d j: %d\n", test, to_check, j);
                            //sth thesh 0 tou buffer row id apo ton R kai sth thesh 1 row id apo ton S

                            int pos = (j==0) ? 0 : r_psum[j-1]->index;
                            //  printf("%d\n", relR[pos + test-1]->value);
                            if (relR[pos + test-1]->value == to_check) {

                                // printf("einai idia\n");
                                //If there is space in buffer
                                if(buffer_pos < 127){
                                    current_buffer->buffer[buffer_pos][0] = relR[pos + test-1]->row_id;
                                    current_buffer->buffer[buffer_pos][1] = relS[k]->row_id;
                                    buffer_pos++;
                                }
                                //Not enough space in current buffer create new node
                                else{
                                    result *new_buffer = createBuffer(current_buffer, 2);
                                    new_buffer->buffer[0][0] = relR[pos + test-1]->row_id;
                                    new_buffer->buffer[0][1] = relS[k]->row_id;
                                    buffer_pos = 1;
                                    current_buffer = new_buffer;
                                }
                            }
                            test = r_bucket_indexes[j]->chain[test-1];
                        }
                    }
                }
            }
        }

        addArray(metadata, 1);
        addArray(metadata, 2);

        return root;
    }
    else{

        printList(*metadata);
        printf("twra tha kanw join me endiamesa apotelesmata\n");

        result *check_buffer = res;
        result *root = createBuffer(NULL, check_buffer->buffer_size + 1);
        result *current_buffer = root;
        int buffer_pos = 0;

        //for all nodes of middle results
        while(check_buffer != NULL){

            //for each row of buffer in node
            for(int i = 0; i < 1024 / (check_buffer->buffer_size * sizeof(int32_t)); i++){

                //check if the buffer is full
                if (check_buffer->buffer[i][0] == -1)
                    break;


                // printf("%d %d S : %d\n", check_buffer->buffer[i][0], check_buffer->buffer[i][1], relA->tuples[check_buffer->buffer[i][1]]->value);
                int h1_value = h1(relA->tuples[check_buffer->buffer[i][1]]->value);

                for (int j = 0; j < r_hist_length; j++) {

                    if (r_psum[j]->hashed_key == h1_value) {

                        int pos = (j==0) ? 0 : r_psum[j-1]->index;
                        //PREPEI NA KSERW WS PROS POIO PINAKA KANW TO JOIN EGW THEWRW EDW OTI KANW SUNEXEIA ME THN TELEUTAIA STHLH STA ENDIAMESA
                        int32_t to_check = relA->tuples[check_buffer->buffer[i][1]]->value;
                        int test = r_bucket_indexes[j]->bucket[h2(to_check)];


                        printf("%d %d\nThesi X : %d\nS : %d\nX : %d\n", check_buffer->buffer[i][0], check_buffer->buffer[i][1], pos + test-1, relA->tuples[check_buffer->buffer[i][1]]->value, relR[pos + test-1]->value);
                        getchar();
                        while (test > 0) {

                            if (relR[pos + test-1]->value == to_check) {

                                printf("einai idia!! i : %d\n\n", i);
                                getchar();
                                //there is space to store the new results
                                if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){

                                    for (int p = 0; p < check_buffer->buffer_size; p++)
                                        current_buffer->buffer[buffer_pos][p] = check_buffer->buffer[i][p];

                                    current_buffer->buffer[buffer_pos][check_buffer->buffer_size] = relR[pos + test-1]->row_id;
                                    buffer_pos++;

                                }
                                else{
                                    printf("Phga se kaiourio buffer\n");
                                    result *new_buffer = createBuffer(current_buffer, check_buffer->buffer_size + 1);

                                    for (int p = 0; p < check_buffer->buffer_size; p++)
                                        new_buffer->buffer[0][p] = check_buffer->buffer[i][p];

                                    new_buffer->buffer[0][check_buffer->buffer_size] = relR[pos + test-1]->row_id;
                                    buffer_pos = 1;
                                    current_buffer = new_buffer;
                                }
                            }
                            test = r_bucket_indexes[j]->chain[test-1];
                        }
                        break;
                    }
                }
            }

            check_buffer = check_buffer->next;
        }

        return root;
    }


}

void printResults(result *root) {

    result *temp = root;
    int i;
    FILE *f = fopen("res.txt", "w");
    fprintf(f, "\n----------------------\n|    R    |     S    |\n----------------------\n");
    while (temp != NULL) {
        i = 0;
        while (temp->buffer[i][0] != -1) {
            fprintf(f, "|   %2d   |    %2d    |\n----------------------\n", temp->buffer[i][0], temp->buffer[i][1]);
            i++;
        }
        temp = temp->next;
    }
    fclose(f);
    return;
}

void printResults2(result *root) {

    result *temp = root;
    int i;
    FILE *f = fopen("res2.txt", "w");
    // fprintf(f, "\n----------------------\n|    R    |     S    |     X    |\n----------------------\n");
    while (temp != NULL) {
        i = 0;
        while (temp->buffer[i][0] != -1) {
            for (size_t j = 0; j < temp->buffer_size; j++) {
                fprintf(f, "|   %2d   ", temp->buffer[i][j]);
            }
                fprintf(f, "|\n----------------------\n");
            i++;
        }
        temp = temp->next;
    }
    fclose(f);
    return;
}

void addArray(query_metadata **ref_arrays, int new_array){


    if ((*ref_arrays) == NULL) {
        printf("edw bazw %d\n", new_array);
        (*ref_arrays) = malloc(sizeof(query_metadata));
        (*ref_arrays)->array_num = new_array;
        (*ref_arrays)->next = NULL;

    }
    else {

        query_metadata *temp = (*ref_arrays);

        while(temp->next != NULL)
            temp = temp->next;

        printf("edw2 bazw %d %d\n", new_array, temp->array_num);
        query_metadata *new_node = malloc(sizeof(query_metadata));
        temp->next = new_node;
        new_node->array_num = new_array;
        new_node->next = NULL;
    }

    return;
}

int searchArray(query_metadata *ref_arrays, int array_num){

    query_metadata *temp = ref_arrays;
    int pos = 0;

    while(temp != NULL){
        if (temp->array_num == array_num)
            return pos;
        temp = temp->next;
        pos++;
    }

    return -1;
}

void printList(query_metadata *ref_arrays){

    query_metadata *temp = ref_arrays;

    printf("Referrenced arrays are : \n");
    while (temp != NULL) {
        printf("%d\n", temp->array_num);
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

result *filterApplication(result *res, int buff_size){

}
