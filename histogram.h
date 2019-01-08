#include <stdint.h>
#include "relation.h"

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

typedef struct histogram {
    int value;
    int freq;
    struct histogram *next;
} histogram;

histogram* searchHistogram(histogram *r_hist, int32_t check);
void addHistogram(histogram **r_hist, int32_t new_value, int32_t freq);
void addFreq(histogram *node, int freq);
int histogramSize(histogram *);

void* createHistogram(int line_start, int line_stop, relation *, histogram* hist);

void destroyHistogram(histogram *r_hist);
void printHistogram(histogram* hist);

#endif