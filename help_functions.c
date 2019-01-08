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

void printOrderedarray(ord_relation** array, int xdimen){
    printf("---------------\n");
    printf("Reordered Array\n");
    for (int i = 0; i < xdimen; i++) {
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

void destroyRandArray(int** xarray, int xdimen){
    for(int i=0; i<xdimen; i++){
        free(xarray[i]);
    }
    free(xarray);
}
