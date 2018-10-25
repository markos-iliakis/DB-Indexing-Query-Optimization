#include <string.h>
#include <time.h>
#include <stdint.h>
#include "relation.h"
#include "hash_functions.h"

#define YDIMEN 4
#define XDIMEN 3
#define COMPARE 2

int main(void){

    srand(time(NULL));
    int **r_array = malloc(XDIMEN * sizeof(int *));
    for (int i = 0; i < XDIMEN; i++)
        r_array[i] = malloc(YDIMEN * sizeof(int));

    int **s_array = malloc(XDIMEN * sizeof(int *));
    for (int i = 0; i < XDIMEN; i++)
        s_array[i] = malloc(YDIMEN * sizeof(int));

    for (int i = 0; i < XDIMEN; i++) {
        for (int j = 0; j < YDIMEN; j++) {
            r_array[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < XDIMEN; i++) {
        for (int j = 0; j < YDIMEN; j++) {
            s_array[i][j] = rand() % 100;
        }
    }

    tuple *r_tuple = malloc(XDIMEN * sizeof(tuple));
    tuple *s_tuple = malloc(YDIMEN * sizeof(tuple));

    for (int i = 0; i < XDIMEN; i++) {
        r_tuple[i].key = h1(r_array[i][COMPARE]);
        r_tuple[i].payload = i;

        s_tuple[i].key = h1(s_array[i][COMPARE]);
        s_tuple[i].payload = i;
    }

    for (size_t i = 0; i < XDIMEN; i++) {
        for (size_t j = 0; j < YDIMEN; j++) {
            printf("%d | ", r_array[i][j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < XDIMEN; i++) {
        printf("%d | %d \n", r_tuple[i].key, r_tuple[i].payload);
    }
}
/*
//find different values for r_tuple and create hist
    int diff;
    for (int i = 0; i < XDIMEN; i++) {

    }

    int **r_hist = malloc(diff*sizeof(int*));
    for (int i = 0; i < diff; i++)
        r_hist = malloc(2*sizeof(int));

    //find different values for s_tuple and create s_hist    int **s_hist = malloc(diff*sizeof(int*));
    for (int i = 0; i < diff; i++)
        s_hist = malloc(2*sizeof(int));
    return 0;
}
*/
