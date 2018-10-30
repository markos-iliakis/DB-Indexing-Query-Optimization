#include "help_functions.h"
#include "hash_functions.h"

 typedef struct bucket_index {
     int *chain;
     int *bucket;
 }bucket_index;


 bucket_index* createBucketIndexes(sum* psum, int hist_length, ord_relation* rel);
 void printChains(bucket_index* buckets, int num_buckets, sum *psum);
 void printChain(int* chain, int size);
