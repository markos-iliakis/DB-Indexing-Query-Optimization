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
    fprintf(stderr, "---------------\n");
    fprintf(stderr, "Histogram\n");
    histogram *temp = r_hist;
    while (temp != NULL) {
        fprintf(stderr, "Value : %3d Frequency : %3d\n", temp->value, temp->freq);
        temp = temp->next;
    }
    fprintf(stderr, "---------------\n");
    getchar();
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

void histogramCompare(histogram* h1, histogram* h2){
    histogram* temp1 = h1;
    histogram* temp2 = h2;
    int flag = 1;

    while(temp1 != NULL){
        if(temp2 == NULL){
            flag = 0;
            break;
        }
        
        if((temp1->value == temp2->value) && (temp1->freq == temp2->freq)){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else{
            flag = 0;
            break;
        }
    }

    fprintf(stderr, "parallel histogram correct : %d\n", flag);
}