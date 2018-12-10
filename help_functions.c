#include "help_functions.h"

// function to print the initial array and it's hash/id array
void printArrayTuple(int** x_array, tuple** x_tuple, int xdimen, int ydimen){
    printf("---------------\n");
    printf("Starting Array\n");
    for (size_t i = 0; i < xdimen; i++) {
        for (size_t j = 0; j < ydimen; j++) {
            printf("%3d | ", x_array[i][j]);
        }
        printf("\n");
    }
    printf("---------------\n");
    printf("Hashed Array\n");
    for (size_t i = 0; i < xdimen; i++) {
        printf("%3d | %3d \n", x_tuple[i]->key, x_tuple[i]->payload);
    }
    printf("---------------\n");
}

// function to make initial random arrays
int** makeRandArray(int xdimen, int ydimen){
    int **rand_array = malloc(xdimen * sizeof(int *));
    for (int i = 0; i < xdimen; i++){
        rand_array[i] = malloc(ydimen * sizeof(int));
        for (size_t j = 0; j < ydimen; j++) {
            rand_array[i][j] = rand() % 10;
        }
    }
    return rand_array;
}

// function to transform initial arrays to hash-value/row-id array
tuple** makeHashIdArray(int64_t** x_array, int xdimen, int colNo){
    tuple **x_tuple = malloc(xdimen * sizeof(tuple *));

    for (int i = 0; i < xdimen; i++) {
        x_tuple[i] = malloc(sizeof(tuple));
        x_tuple[i]->key = h1(x_array[colNo][i]);
        x_tuple[i]->payload = i;
        x_tuple[i]->value = x_array[colNo][i];
    }
    return x_tuple;
}

histogram* createHistogram(int xdimen, relation *rel){

    histogram* hist = NULL;

    for (int i = 0; i < xdimen; i++) {
        histogram *temp = searchHistogram(hist, rel->tuples[i]->key);
        if (temp == NULL)
            addHistogram(&hist, rel->tuples[i]->key);
        else
            addFreq(temp);
    }

    return hist;
}

//function to serach a hash value in histogram
histogram* searchHistogram(histogram *r_hist, int32_t check){

    histogram *temp = r_hist;

    while (temp != NULL) {
        if(temp->value == check)
            return temp;
        else
            temp = temp->next;
    }

    return NULL;
}

void addHistogram(histogram **r_hist, int32_t new_value) {

    histogram *temp = *r_hist;

    if ((*r_hist) == NULL) {
        // printf("Prwth eisagwgh\n");
        (*r_hist) = malloc(sizeof(histogram));
        (*r_hist)->value = new_value;
        (*r_hist)->freq = 1;
        (*r_hist)->next = NULL;
    }
    else{
        while (temp->next != NULL)
            temp = temp->next;

        histogram *new_node = malloc(sizeof(histogram));
        temp->next = new_node;
        new_node->next = NULL;
        new_node->value = new_value;
        new_node->freq = 1;
    }
    return;
}

void addFreq(histogram *node) {
    node->freq++;
}

void destroyHistogram(histogram *r_hist){

    histogram *temp = r_hist->next;
    while (temp->next != NULL) {
        free(r_hist);
        r_hist = temp;
        temp = r_hist->next;
    }

    free(temp);
    temp = NULL;

    if(r_hist != NULL)
        free(r_hist);
    return;
}

void printHistogram(histogram *r_hist){

    printf("---------------\n");
    printf("Histogram\n");
    histogram *temp = r_hist;
    while (temp != NULL) {
        printf("Value : %3d Frequency : %3d\n", temp->value, temp->freq);
        temp = temp->next;
    }
    printf("---------------\n");

}

int histogramSize(histogram *r_hist){

    int length = 0;
    histogram *temp = r_hist;
    while(temp != NULL){
        length++;
        temp = temp->next;
    }

    return length;

}

sum** createPsum(int hist_length, histogram* hist){

    sum** psum = malloc(hist_length*sizeof(sum*));
    histogram *temp1 = hist, *temp2 = hist->next;

    int sum = 0;
    for (int i = 0; i < hist_length; i++) {
        psum[i] = malloc(sizeof(**psum));
        if(i==0){
            psum[i]->index = 0;
            psum[i]->hashed_key = hist->value;
        }
        else{
            psum[i]->index = sum + temp1->freq;
            psum[i]->hashed_key = temp2->value;
            sum += temp1->freq;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    return psum;
}

int searchPsum(int length, int value, sum **psum) {
    for (int i = 0; i < length; i++) {
        if (psum[i]->hashed_key == value)
            return i;
    }

    return -1;
}

void printPsum(sum** psum, int hist_length){
    printf("---------------\n");
    printf("Psum\n");
    for (int i = 0; i < hist_length; i++) {
        printf("Value : %3d Index : %3d\n", psum[i]->hashed_key, psum[i]->index);
    }
    printf("---------------\n");
}

ord_relation** createReorderedarray(sum **psum, int size, relation *r_relation, int xdimen){

    ord_relation** new_array = malloc(xdimen * sizeof(ord_relation *));

    // for each row of r
    for (int i = 0; i < xdimen; i++) {
        new_array[i] = malloc(sizeof(ord_relation));
    }
    for (int i = 0; i < xdimen; i++) {
        for(int j = 0; j < size; j++){
            // if we have found the same hashed_key
            if(r_relation->tuples[i]->key == psum[j]->hashed_key){
                new_array[psum[j]->index]->row_id = r_relation->tuples[i]->payload;
                new_array[psum[j]->index]->value = r_relation->tuples[i]->value;
                psum[j]->index++;
                break;
            }
        }
    }

    return new_array;
}

void printOrderedarray(ord_relation** array){
    printf("---------------\n");
    printf("Reordered Array\n");
    for (int i = 0; i < XDIMEN; i++) {
        printf("RowId : %2d Value %2d\n", array[i]->row_id, array[i]->value);
    }
    printf("---------------\n");
}

void destroyOrdArray(ord_relation** ord, int size){
    for(int i=0; i < size; i++){
        free(ord[i]);
    }
    free(ord);
}

void destroySum(sum** psum, int size){
    for (int i = 0; i < size; i++)
        free(psum[i]);
    free(psum);
}

void destroyRelation(relation* rel){

    for(int i=0; i < rel->num_tuples; i++){
        free(rel->tuples[i]);
    }
    free(rel->tuples);

    free(rel);
}

void destroyRandArray(int** xarray, int xdimen){
    for(int i=0; i<xdimen; i++){
        free(xarray[i]);
    }
    free(xarray);
}
