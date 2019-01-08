#include "histogram.h"

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

void addHistogram(histogram **r_hist, int32_t new_value, int32_t freq) {

    histogram *temp = *r_hist;

    if ((*r_hist) == NULL) {
        // printf("Prwth eisagwgh\n");
        (*r_hist) = malloc(sizeof(histogram));
        (*r_hist)->value = new_value;
        (*r_hist)->freq = freq;
        (*r_hist)->next = NULL;
    }
    else{
        while (temp->next != NULL)
            temp = temp->next;

        histogram *new_node = malloc(sizeof(histogram));
        temp->next = new_node;
        new_node->next = NULL;
        new_node->value = new_value;
        new_node->freq = freq;
    }
    return;
}

void addFreq(histogram *node, int freq) {
    node->freq += freq;
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