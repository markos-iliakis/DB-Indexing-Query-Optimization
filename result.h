#ifndef RESULT_H
#define RESULT_H

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

void addArray(query_metadata **, int new_array);
int searchArray(query_metadata *, int array_num, int appearence);
void printList(query_metadata *);

result* createBuffer(result *prev, int);
result* RadixHashJoin(result *res, ord_relation **relR, ord_relation **relS, bucket_index **r_bucket_indexes, sum **r_psum, sum **s_psum, int r_hist_length, int s_hist_length, relation *, int array_pos);
result* joinValue(result *res, ord_relation **ord_relR, bucket_index **r_bucket_indexes, sum **r_psum, int r_hist_length, relation *relR, int compare_value, int array_pos);
result* filterApplication(query_metadata *, result *res, int buff_size, relation *, int op, int tot_rows, int c_value, int col_num, int rel_num, int appearance_rel1);
result* selfJoin(result *, relation *, relation *, int, int);
result *joinArrays(result *res, relation *relR, relation *relS, int array_posR, int array_posS);

void destroyResult(result* r);
void destroyResult(result* r);
void executeQuery(Queue* q, indexes_array* index, proj_list* pl);
void checkSum(result* res, proj_list* pl, indexes_array* index, query_metadata* metadata);


int parseInstuctions(indexes_array* indexes);
#endif