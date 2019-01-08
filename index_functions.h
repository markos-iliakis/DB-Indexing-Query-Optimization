#include "sum.h"
#include "hash_functions.h"
#include "job_scheduler.h"
#include "help_functions.h"

#ifndef INDEX_FUNCTIONS_H
#define INDEX_FUNCTIONS_H

 typedef struct bucket_index {
     int *chain;
     int *bucket;
 }bucket_index;

typedef struct indexes{
    int colNum;
    relation **array_relations;
    histogram **array_histograms;
    sum ***array_psums;
    ord_relation ***ord_relations;
    bucket_index ***array_bucket_indexes;    
}indexes;

typedef struct indexes_array{
    indexes** ind;
    int size;
}indexes_array;

bucket_index** createBucketIndexes(sum** psum, int hist_length, ord_relation** rel);
void printChains(bucket_index** buckets, int num_buckets, sum** psum);
void printChain(int* chain, int size);
void destroyBucketIndexes(bucket_index** ind, int size);
indexes_array* createIndexes(tb_array* tb);
void destroyIndexes(indexes_array* indexes);
#endif