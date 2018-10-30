#include "help_functions.h"
#include "hash_functions.h"

 typedef struct bucket_index {
     int *chain;
     int *bucket;
 }bucket_index;


 bucket_index* createBucketIndexes(sum* psum, int hist_length, ord_relation* rel);
 void printBuckets(bucket_index *, int , sum *);
