#include "help_functions.h"

// function to print the initial array and it's hash/id array
void printArrayTuple(int** x_array, tuple* x_tuple, int xdimen, int ydimen){
    for (size_t i = 0; i < xdimen; i++) {
        for (size_t j = 0; j < ydimen; j++) {
            printf("%d | ", x_array[i][j]);
        }
        printf("\n");
    }
    printf("---------------\n");
    for (size_t i = 0; i < xdimen; i++) {
        printf("%d | %d \n", x_tuple[i].key, x_tuple[i].payload);
    }
    printf("---------------\n");
}

// function to make initial random arrays
int** makeRandArray(int xdimen, int ydimen){
    int **rand_array = malloc(xdimen * sizeof(int *));
    for (int i = 0; i < xdimen; i++){
        rand_array[i] = malloc(ydimen * sizeof(int));
        for (size_t j = 0; j < ydimen; j++) {
            rand_array[i][j] = rand() % 100;
        }
    }
    return rand_array;
}

// function to transform initial arrays to hash-value/row-id array
tuple* makeHashIdArray(int** x_array, int xdimen){
    tuple *x_tuple = malloc(xdimen * sizeof(tuple));

    for (int i = 0; i < xdimen; i++) {
        x_tuple[i].key = h1(x_array[i][COMPARE]);
        x_tuple[i].payload = i;
    }
    return x_tuple;
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
        printf("Prwth eisagwgh\n");
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
    return;
}

void destroyHistogram(histogram *r_hist){

    histogram *temp = r_hist->next;
    while (temp->next != NULL) {
        free(r_hist);
        r_hist = temp;
        temp = temp->next;
    }

    free(temp);
    temp = NULL;
    return;
}

void printHistogram(histogram *r_hist){

    histogram *temp = r_hist;
    while (temp != NULL) {
        printf("Value : %d Frequency %d\n", temp->value, temp->freq);
        temp = temp->next;
    }

}
