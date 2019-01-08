#include "sum.h"

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

void destroySum(sum** psum, int size){
    for (int i = 0; i < size; i++)
        free(psum[i]);
    free(psum);
}