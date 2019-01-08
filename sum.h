#include "histogram.h"

#ifndef SUM_H
#define SUM_H

typedef struct sum {
    int hashed_key;
    int index;
}sum;

void printPsum(sum** psum, int hist_length);

sum** createPsum(int hist_length, histogram* hist);
int searchPsum(int length, int value, sum **psum);

void destroySum(sum** psum, int size);

#endif