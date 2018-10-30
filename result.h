#include "index_functions.h"

struct result;

typedef struct result {
    int32_t **buffer;
    struct result *next;
} result;

result* RadixHashJoin(ord_relation *relR, ord_relation *relS, bucket_index *r_bucket_indexes, sum *r_psum, sum *s_psum, int r_hist_length, int s_hist_length);
