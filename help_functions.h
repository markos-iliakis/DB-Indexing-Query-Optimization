#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "relation.h"
#include "hash_functions.h"
#include <string.h>
#include <time.h>
#include <stdint.h>
// #include "job_scheduler.h"

#define DISTINCT 30

#define YDIMEN 4
#define XDIMEN 10
#define COMPARE 2

struct histogram;

typedef struct histogram {
    int value;
    int freq;
    struct histogram *next;
} histogram;

typedef struct sum {
    int hashed_key;
    int index;
}sum;

void printArrayTuple(int** x_array, tuple** x_tuple, int xdimen, int ydimen);
int** makeRandArray(int xdimen, int ydimen);
tuple** makeHashIdArray(int64_t** x_array, int xdimen, int col_no);
histogram* searchHistogram(histogram *r_hist, int32_t check);
void addHistogram(histogram **r_hist, int32_t new_value, int32_t freq);
void addFreq(histogram *node, int freq);
void destroyHistogram(histogram *r_hist);
void printHistogram(histogram* hist);
void printPsum(sum** psum, int hist_length);
int histogramSize(histogram *);
sum** createPsum(int hist_length, histogram* hist);
int searchPsum(int length, int value, sum **psum);
ord_relation** createReorderedarray(sum **psum, int size, relation *r_relation, int xdimen);
void printOrderedarray(ord_relation **array);
histogram* createParallelHistogram(int tot_num, relation* rel);
void* createHistogram(int line_start, int line_stop, relation *, histogram* hist);
void destroyOrdArray(ord_relation** ord, int size);
void destroySum(sum** psum, int size);
void destroyRelation(relation* rel);
void destroyRandArray(int** xarray, int xdimen);
#endif