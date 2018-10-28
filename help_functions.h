#include "relation.h"
#include "hash_functions.h"
#include <string.h>
#include <time.h>
#include <stdint.h>

#define YDIMEN 4
#define XDIMEN 100
#define COMPARE 2

struct histogram;

typedef struct histogram {
    int value;
    int freq;
    struct histogram *next;
} histogram;

void printArrayTuple(int** x_array, tuple* x_tuple, int xdimen, int ydimen);
int** makeRandArray(int xdimen, int ydimen);
tuple* makeHashIdArray(int** x_array, int xdimen);
histogram* searchHistogram(histogram *r_hist, int32_t check);
void addHistogram(histogram **r_hist, int32_t new_value);
void addFreq(histogram *node);
void destroyHistogram(histogram *r_hist);
void printHistogram(histogram *r_hist);
int histogramSize(histogram *);
void createPsum(histogram *, histogram *, int);
int** createReorderedarray(histogram *r_relation, relation *psum, int xdimen, int ydimen) ;
void printPsum(histogram* psum, int hist_length);
