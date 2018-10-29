

 typedef struct bucket_index {
     int *chain;
     int *bucket;
 }buckeet_index;


 bucket_index* createBucketIndexes(sum* psum, int hist_length, relation* rel);
