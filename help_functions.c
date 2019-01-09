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
void makeRandArray(st_table** rand_tb){
    (*rand_tb)->col = malloc((*rand_tb)->colNum * sizeof(int64_t*));
        for (int j = 0; j < (*rand_tb)->colNum; j++){
            (*rand_tb)->col[j] = malloc((*rand_tb)->rowNum * sizeof(int64_t));
            for (int k = 0; k < (*rand_tb)->rowNum; k++) {
                (*rand_tb)->col[j][k] = rand() % 10;
            }
        }
}

void loadTestTables(tb_array** tb, int tables_num, int xdimen, int ydimen){
    *tb = malloc(sizeof(tb_array));
    (*tb)->size = tables_num;
    (*tb)->tb = malloc((*tb)->size * sizeof(st_table*));

    for(int i=0; i < (*tb)->size; i++){
        (*tb)->tb[i] = malloc(sizeof(st_table));
        (*tb)->tb[i]->colNum = ydimen;
        (*tb)->tb[i]->rowNum = xdimen;

        makeRandArray(&((*tb)->tb[i]));
        printTestTable((*tb)->tb[i]);
    }
}

void printTestTable(st_table* tb){
    printf("---------------\n");
    printf("Starting Array\n");
    for(int i=0; i < tb->rowNum; i++){
        for(int j=0; j < tb->colNum; j++){
            printf("%3ld | ", tb->col[j][i]);
        }
        printf("\n");
    }
    printf("---------------\n");
    getchar();
}

void printTestColumnHashed(tuple** tup, int tupNum){
    printf("---------------\n");
    printf("Hashed Array\n");
    for (size_t i = 0; i < tupNum; i++) {
        printf("%3d | %3d \n", tup[i]->key, tup[i]->value);
    }
    printf("---------------\n");
    getchar();
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
