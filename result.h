#include "index_functions.h"
#include "queue.h"

struct result;
struct query_metadata;

typedef struct result {
    int32_t **buffer;
    int buffer_size;
    struct result *next;
} result;

typedef struct query_metadata{
    int array_num;
    struct query_metadata *next;
}query_metadata;

void printResults(result *root);
void printResults2(result *root);

void addArray(query_metadata **, int);
int searchArray(query_metadata *, int);
void printList(query_metadata *);

result* createBuffer(result *prev, int);
result* RadixHashJoin(result *res, ord_relation **relR, ord_relation **relS, bucket_index **r_bucket_indexes, sum **r_psum, sum **s_psum, int r_hist_length, int s_hist_length, relation *, int array_pos);
result* filterApplication(query_metadata *, result *res, int buff_size, relation *, int op, int tot_rows, int c_value, int col_num, int);

void destroyResult(result* r);
void destroyResult(result* r);
void executeQuery(Queue* q, indexes **index, proj_list* pl);
void checkSum(result* res, proj_list* pl, indexes** index, query_metadata* metadata);