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

void executeQuery(Queue* q, indexes_array* index, proj_list* pl){
    //estw edw oti exome to priority queue
    //ekteloume bhma bhma ta nodes pou einai mesa sthn priority queue
    query_metadata *metadata = NULL;
    result *prev = NULL, *res = NULL;

    for(int i=q->front; i< q->size; i++){

        // table 1
        int rel_num = q->array[i]->t1->table;
        int col_num = q->array[i]->t1->column;
        int op = q->array[i]->op;
        int appearance_rel1 = q->array[i]->t1->appearance;
        int appearance_rel2 = q->array[i]->t2->appearance;   
        int tot_rows = index->ind[rel_num]->array_relations[col_num]->num_tuples;
        int c_value = q->array[i]->t2->table;

        //exw filtro
        if(q->array[i]->op == 1 || q->array[i]->op == 2){
            // printf("applying filter %d.%d-%d\n", rel_num, col_num, c_value);
            //na ftiaksoume sunarthsh na efarmozei filtro kai na epostrefei result *
            if(prev == NULL){
                // printf("applying filter %d.%d-%d\n", rel_num, col_num, c_value);
                prev = filterApplication(NULL, NULL, 1, index->ind[rel_num]->array_relations[col_num], op, tot_rows, c_value, col_num, rel_num, appearance_rel1);
                //edw tha prepei na bazoume sta metadata ton pinaka pou xrhsimopoihsame
                // printf("Bazw sthn oura ton pinaka %d\n", q->array[i]->t1->table);
                printResults2(prev);
                addArray(&metadata, q->array[i]->t1->table);
            }
            else{
                res = filterApplication(metadata, prev, prev->buffer_size, index->ind[rel_num]->array_relations[col_num], op, tot_rows, c_value, col_num, rel_num, appearance_rel1);
                if(searchArray(metadata, q->array[i]->t1->table, appearance_rel1) >= 0)
                    addArray(&metadata, q->array[i]->t1->table);
            }
        }
        //exw join pinakwn
        else if(q->array[i]->op == 0){

            int rel_num2 = q->array[i]->t2->table;
            int col_num2 = q->array[i]->t2->column;

            int tot_rows2 = index->ind[rel_num]->array_relations[col_num]->num_tuples;
            int hist_length1 = histogramSize(index->ind[rel_num]->array_histograms[col_num]);
            int hist_length2 = histogramSize(index->ind[rel_num2]->array_histograms[col_num2]);

            if(prev == NULL){

                if(rel_num != rel_num2){
                    //size of rel_num > size of rel_num2
                    if(tot_rows > tot_rows2){
                        prev = RadixHashJoin(NULL, index->ind[rel_num]->ord_relations[col_num], index->ind[rel_num2]->ord_relations[col_num2],
                            index->ind[rel_num]->array_bucket_indexes[col_num], index->ind[rel_num]->array_psums[col_num],
                            index->ind[rel_num]->array_psums[col_num2], hist_length1, hist_length2, NULL, -1);
                        addArray(&metadata, rel_num);
                        addArray(&metadata, rel_num2);
                    }
                    else{
                        prev = RadixHashJoin(NULL, index->ind[rel_num2]->ord_relations[col_num2], index->ind[rel_num]->ord_relations[col_num], index->ind[rel_num2]->array_bucket_indexes[col_num2], index->ind[rel_num2]->array_psums[col_num2], index->ind[rel_num]->array_psums[col_num], hist_length2, hist_length1, NULL, -1);
                    }
                }
                //self join
                else{
                    prev = selfJoin(NULL, index->ind[rel_num2]->array_relations[col_num], index->ind[rel_num2]->array_relations[col_num2], tot_rows, -1);
                    addArray(&metadata, rel_num);
                }

            }
            else{
                int pos = -1;
                int pos2 = -1;
                //size of rel_num > size of rel_num2
                if((pos = searchArray(metadata, rel_num, appearance_rel1)) >= 0 && (pos2 = searchArray(metadata, rel_num2, appearance_rel2)) == -1){
                    addArray(&metadata, rel_num2);
                    // printf("applying join %d.%d = %d.%d\n", rel_num, col_num, rel_num2, col_num2);
                    res = RadixHashJoin(prev, index->ind[rel_num2]->ord_relations[col_num2], NULL, index->ind[rel_num2]->array_bucket_indexes[col_num2], index->ind[rel_num2]->array_psums[col_num2], NULL, hist_length2, -1, index->ind[rel_num]->array_relations[col_num], pos);
                    printResults2(res);
                }

                else if((pos = searchArray(metadata, rel_num2, appearance_rel2)) >= 0 && (pos2 = searchArray(metadata, rel_num, appearance_rel1)) == -1){
                    // printf("2 -- applying join %d.%d = %d.%d\n", rel_num, col_num, rel_num2, col_num2);
                    addArray(&metadata, rel_num);
                    res = RadixHashJoin(prev, index->ind[rel_num]->ord_relations[col_num], NULL, index->ind[rel_num]->array_bucket_indexes[col_num], index->ind[rel_num]->array_psums[col_num], NULL, hist_length1, -1, index->ind[rel_num2]->array_relations[col_num2], pos);
                }
                //self join
                else if((pos = searchArray(metadata, rel_num2, appearance_rel2)) >= 0 && (pos2 = searchArray(metadata, rel_num, appearance_rel1)) >= 0 && pos == pos2){
                    // printf("applying Self join %d.%d = %d.%d pos : %d\n", rel_num, col_num, rel_num2, col_num2, pos);

                    //logika tha thelei orisma na an exw self join pinaka o opoiow brisketai 2 fores sta endiamesa apotelesmata
                    //se poia sthlh brisketai kai o deuteros ???
                    res = selfJoin(prev, index->ind[rel_num2]->array_relations[col_num], index->ind[rel_num2]->array_relations[col_num2], tot_rows, pos);

                }
                // periptwsh pou oi 2 pinakes einai sta endiamesa apotelesmata kai einai diaforetikoi
                else if((pos = searchArray(metadata, rel_num, appearance_rel1)) >= 0 && (pos2 = searchArray(metadata, rel_num2, appearance_rel2)) >= 0 && pos != pos2){
                    // printf("applying MIDDLE join %d.%d = %d.%d pos : %d\n", rel_num, col_num, rel_num2, col_num2, pos);
                    res = joinArrays(prev, index->ind[rel_num]->array_relations[col_num], index->ind[rel_num2]->array_relations[col_num2], pos, pos2);
                }
                // periptwsh pou to join 2 pinakwn den einai sta endiamesa apotelesamta
                else{
                         printf("applying AKURO JOIN PINAKWN %d.%d = %d.%d pos : %d\n", rel_num, col_num, rel_num2, col_num2, pos);
                //      //kalese th radix kateutheian
                //     // trekse osa operations xreiazontai etsi wste ta 2 endiamesa apotelesmata na ginoun 1
                //     // proxwra kai to i
                //
                }
            }
        }
        else{
            if(prev == NULL){
                // printf("applying join filter %d.%d-%d\n", rel_num, col_num, c_value);
                int hist_length1 = histogramSize(index->ind[rel_num]->array_histograms[col_num]);
                addArray(&metadata, q->array[i]->t1->table);
                prev = joinValue(NULL, index->ind[rel_num]->ord_relations[col_num], index->ind[rel_num]->array_bucket_indexes[col_num],
                    index->ind[rel_num]->array_psums[col_num], hist_length1, index->ind[rel_num]->array_relations[col_num], c_value,-1);
            }
            else{
                // printf("applying join filter %d.%d-%d\n", rel_num, col_num, c_value);
                int array_pos = searchArray(metadata, rel_num, appearance_rel1);
                prev = joinValue(NULL, NULL, NULL, NULL, -1, index->ind[rel_num]->array_relations[col_num], c_value, array_pos);
            }
        }
        if(i != q->front){
            destroyResult(prev);
            prev = res;
            res = NULL;
        }
    }
    //to teliko reuslt pou exei bgei bgazoume cheksum

    checkSum(prev, pl, index, metadata);
    destroyResult(prev);

}

void checkSum(result* res, proj_list* pl, indexes_array* index, query_metadata *metadata){

    proj_list* temp = pl;


    while(temp != NULL){
        uint64_t sum = 0;

        int array_pos = searchArray(metadata, temp->t->table, temp->t->appearance);
        result *tmp = res;
        while(tmp != NULL){


            for(int i = 0; i< 1024 / tmp->buffer_size * sizeof(int32_t); i++){
                if(tmp->buffer[i][0] == -1)
                    break;
                sum += index->ind[temp->t->table]->array_relations[temp->t->column]->tuples[tmp->buffer[i][array_pos]]->value;
            }
            tmp = tmp->next;
        }
        printf("\nChecksum of %d.%d : %ld\n", temp->t->table, temp->t->column, sum);
        temp = temp->next;
    }

}

result* filterApplication(query_metadata *metadata, result *res, int buff_size, relation *relA, int op, int tot_rows, int c_value, int col_num, int rel_num, int appearance_rel1){

    int buffer_pos = 0;
    result* root = NULL;
    result* current_buffer;
    result* check_buffer = res;

    // if there is not previus result start making this one from scratch
    if(res == NULL){
        root = createBuffer(NULL, buff_size);
        current_buffer = root;

        for(int i=0; i < tot_rows; i++){

            //greater operation
            if(op == 1){

                if(relA->tuples[i]->value < c_value){

                    //there is space in buffer
                    if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){
                        current_buffer->buffer[buffer_pos][0] = i;
                        buffer_pos++;
                    }
                    else{
                        result *new_buffer = createBuffer(current_buffer, buff_size);
                        new_buffer->buffer[0][0] = i;
                        buffer_pos = 1;
                        current_buffer = new_buffer;
                    }
                }
            }
            //lesser operation
            else{

                if(relA->tuples[i]->value > c_value){

                    //there is space in buffer
                    if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){
                        current_buffer->buffer[buffer_pos][0] = i;
                        buffer_pos++;
                    }
                    else{
                        result *new_buffer = createBuffer(current_buffer, buff_size);
                        new_buffer->buffer[0][0] = i;
                        buffer_pos = 1;
                        current_buffer = new_buffer;
                    }
                }
            }
        }
    }
    else {
        root = createBuffer(NULL, check_buffer->buffer_size);
        current_buffer = root;
        int array_pos = searchArray(metadata, rel_num, appearance_rel1);
        while(check_buffer != NULL){

            for(int i = 0; i < 1024 / (check_buffer->buffer_size * sizeof(int32_t)); i++){

                if(op == 1){

                    if(relA->tuples[check_buffer->buffer[i][array_pos]]->value > c_value){

                        if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){

                            for (int p = 0; p < check_buffer->buffer_size; p++)
                                current_buffer->buffer[buffer_pos][p] = check_buffer->buffer[i][p];

                            buffer_pos++;

                        }
                        else{

                            result *new_buffer = createBuffer(current_buffer, check_buffer->buffer_size + 1);

                            for (int p = 0; p < check_buffer->buffer_size; p++)
                                new_buffer->buffer[0][p] = check_buffer->buffer[i][p];

                            buffer_pos = 1;
                            current_buffer = new_buffer;
                        }
                    }
                }
                else{
                     if(relA->tuples[check_buffer->buffer[i][array_pos]]->value < c_value){

                        if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){

                            for (int p = 0; p < check_buffer->buffer_size; p++)
                                current_buffer->buffer[buffer_pos][p] = check_buffer->buffer[i][p];

                            buffer_pos++;

                        }
                        else{

                            result *new_buffer = createBuffer(current_buffer, check_buffer->buffer_size + 1);

                            for (int p = 0; p < check_buffer->buffer_size; p++)
                                new_buffer->buffer[0][p] = check_buffer->buffer[i][p];

                            buffer_pos = 1;
                            current_buffer = new_buffer;
                        }
                    }
                }
            }
            check_buffer = check_buffer->next;
        }
    }

    return root;
}

result* RadixHashJoin(result *res, ord_relation **relR, ord_relation **relS, bucket_index **r_bucket_indexes, sum **r_psum, sum **s_psum, int r_hist_length, int s_hist_length, relation *relA, int array_pos){

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

        return root;
    }
    else{

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
                int h1_value = h1(relA->tuples[check_buffer->buffer[i][array_pos]]->value);

                for (int j = 0; j < r_hist_length; j++) {

                    if (r_psum[j]->hashed_key == h1_value) {

                        int pos = (j==0) ? 0 : r_psum[j-1]->index;
                        //PREPEI NA KSERW WS PROS POIO PINAKA KANW TO JOIN EGW THEWRW EDW OTI KANW SUNEXEIA ME THN TELEUTAIA STHLH STA ENDIAMESA
                        int32_t to_check = relA->tuples[check_buffer->buffer[i][array_pos]]->value;
                        int test = r_bucket_indexes[j]->bucket[h2(to_check)];

                        while (test > 0) {

                            if (relR[pos + test-1]->value == to_check) {

                                // printf("einai idia!! i : %d\n\n", i);
                                // getchar();
                                //there is space to store the new results
                                if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){

                                    for (int p = 0; p < check_buffer->buffer_size; p++)
                                        current_buffer->buffer[buffer_pos][p] = check_buffer->buffer[i][p];

                                    current_buffer->buffer[buffer_pos][check_buffer->buffer_size] = relR[pos + test-1]->row_id;
                                    buffer_pos++;

                                }
                                else{
                                    // printf("Phga se kaiourio buffer\n");
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

result* joinValue(result *res, ord_relation **ord_relR, bucket_index **r_bucket_indexes, sum **r_psum, int r_hist_length, relation *relR, int compare_value, int array_pos){

    if (res == NULL) {

        result *root = createBuffer(NULL, 1);
        result *current_buffer = root;
        int buffer_pos = 0;

        int check_value = h1(compare_value);

        for (int i = 0; i < r_hist_length; i++) {

            if(r_psum[i]->hashed_key == check_value){

                int test = test = r_bucket_indexes[i]->bucket[h2(compare_value)];

                while (test > 0) {

                    int pos = (i==0) ? 0 : r_psum[i-1]->index;
                    if(ord_relR[pos + test-1]->value == compare_value){
                        if(buffer_pos < 127){
                            current_buffer->buffer[buffer_pos][0] = ord_relR[pos + test-1]->row_id;
                            buffer_pos++;
                        }
                        //Not enough space in current buffer create new node
                        else{
                            result *new_buffer = createBuffer(current_buffer, 2);
                            new_buffer->buffer[0][0] = ord_relR[pos + test-1]->row_id;
                            buffer_pos = 1;
                            current_buffer = new_buffer;
                        }
                    }
                    test = r_bucket_indexes[i]->chain[test-1];
                }
            }
        }

        return root;
    }
    else{

        // printf("kanw join mw timh sta endiamesa\n");
        result *check_buffer = res;
        result *root = createBuffer(NULL,  check_buffer->buffer_size);
        result *current_buffer = root;
        int buffer_pos = 0;

        while(check_buffer != NULL){

            for(int i = 0; i < 1024 / (check_buffer->buffer_size * sizeof(int32_t)); i++){

                if (check_buffer->buffer[i][0] == -1)
                    break;

                if(relR->tuples[check_buffer->buffer[i][array_pos]]->value == compare_value){

                    if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){

                        for (int p = 0; p < check_buffer->buffer_size; p++)
                            current_buffer->buffer[buffer_pos][p] = check_buffer->buffer[i][p];

                        buffer_pos++;
                    }
                    else{

                        result *new_buffer = createBuffer(current_buffer, check_buffer->buffer_size);

                        for (int p = 0; p < check_buffer->buffer_size; p++)
                            new_buffer->buffer[0][p] = check_buffer->buffer[i][p];

                        buffer_pos = 1;
                        current_buffer = new_buffer;
                    }
                }
            }
            check_buffer = check_buffer->next;
        }

        return root;
    }
}

//function to join different columns of same array
result* selfJoin(result *res, relation *relColA, relation *relColB, int total_rows, int array_pos){

    if(res == NULL){

        result *root = createBuffer(NULL, 1);
        result *current_buffer = root;

        int buffer_pos = 0;
        for (int i = 0; i < total_rows; i++) {
            if (relColA->tuples[i]->value == relColB->tuples[i]->value) {
                if(buffer_pos < 127){
                    current_buffer->buffer[buffer_pos][0] = i;
                    buffer_pos++;
                }
                //Not enough space in current buffer create new node
                else{
                    result *new_buffer = createBuffer(current_buffer, 2);
                    new_buffer->buffer[0][0] = i;
                    buffer_pos = 1;
                    current_buffer = new_buffer;
                }
            }
        }
        return root;
    }
    else{

        result *check_buffer = res;
        result *root = createBuffer(NULL,  check_buffer->buffer_size);
        result *current_buffer = root;
        int buffer_pos = 0;

        while(check_buffer != NULL){

            for (int i = 0; i < 1024 / (check_buffer->buffer_size * sizeof(int32_t)); i++) {

                if (check_buffer->buffer[i][0] == -1)
                    break;

                if(relColA->tuples[check_buffer->buffer[i][array_pos]]->value == relColB->tuples[check_buffer->buffer[i][array_pos]]->value){

                    if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){

                        for (int p = 0; p < check_buffer->buffer_size; p++)
                            current_buffer->buffer[buffer_pos][p] = check_buffer->buffer[i][p];

                        buffer_pos++;
                    }
                    else{

                        result *new_buffer = createBuffer(current_buffer, check_buffer->buffer_size);

                        for (int p = 0; p < check_buffer->buffer_size; p++)
                            new_buffer->buffer[0][p] = check_buffer->buffer[i][p];

                        buffer_pos = 1;
                        current_buffer = new_buffer;
                    }
                }
            }
            check_buffer = check_buffer->next;
        }

        return root;
    }
}

//function to join 2 arrays placed in middle results
result *joinArrays(result *res, relation *relR, relation *relS, int array_posR, int array_posS){

    result *check_buffer = res;
    result *root = createBuffer(NULL,  check_buffer->buffer_size);
    result *current_buffer = root;
    int buffer_pos = 0;

    while (check_buffer != NULL) {

        for (int i = 0; i < 1024 / (check_buffer->buffer_size * sizeof(int32_t)); i++) {

            if (check_buffer->buffer[i][0] == -1)
                break;

            if(relR->tuples[check_buffer->buffer[i][array_posR]]->value == relS->tuples[check_buffer->buffer[i][array_posS]]->value){

                if(buffer_pos < current_buffer->buffer_size * sizeof(int32_t)){

                    for (int p = 0; p < check_buffer->buffer_size; p++)
                        current_buffer->buffer[buffer_pos][p] = check_buffer->buffer[i][p];

                    buffer_pos++;
                }
                else{

                    result *new_buffer = createBuffer(current_buffer, check_buffer->buffer_size);

                    for (int p = 0; p < check_buffer->buffer_size; p++)
                        new_buffer->buffer[0][p] = check_buffer->buffer[i][p];

                    buffer_pos = 1;
                    current_buffer = new_buffer;
                }
            }
        }
        check_buffer = check_buffer->next;
    }

    return root;
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
        // printf("edw bazw %d\n", new_array);
        (*ref_arrays) = malloc(sizeof(query_metadata));
        (*ref_arrays)->array_num = new_array;
        (*ref_arrays)->next = NULL;

    }
    else {

        query_metadata *temp = (*ref_arrays);

        while(temp->next != NULL)
            temp = temp->next;

        // printf("edw2 bazw %d %d\n", new_array, temp->array_num);
        query_metadata *new_node = malloc(sizeof(query_metadata));
        temp->next = new_node;
        new_node->array_num = new_array;
        new_node->next = NULL;
    }

    return;
}

int searchArray(query_metadata *ref_arrays, int array_num, int appearence){

    query_metadata *temp = ref_arrays;
    int pos = 0;
    int appearance_num = 0;
    while(temp != NULL){
        if (temp->array_num == array_num && appearance_num == appearence)
            return pos;
        else if(temp->array_num == array_num)
            appearance_num++;
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
        for(int i = 0; i < 1024 / (temp->buffer_size * sizeof(int32_t)); i++) {
            free(temp->buffer[i]);
        }
        free(temp->buffer);
        free(temp);
        temp = r;
    }
}
