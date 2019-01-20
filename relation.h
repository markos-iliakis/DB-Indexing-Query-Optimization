#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdbool.h>

#ifndef RELATION_H
#define RELATION_H

/** Type definition for a tuple */
struct tuple;
struct relation;
struct result;
struct stat_array;
struct stat_holder;

typedef struct tuple {
    int32_t key;
    int32_t payload; //row_id
    int32_t value;
} tuple;

/**
* Type definition for a relation.
* It consists of an array of tuples and a size of the relation.
*/
typedef struct relation {
    tuple** tuples;
    uint32_t num_tuples;
} relation;

typedef struct ord_relation {
    int32_t row_id;
    int32_t value;
} ord_relation;

typedef struct st_table {
    int colNum;
    int rowNum;
    int64_t** col;
} st_table;

typedef struct tb_array {
    st_table** tb;
    int size;
} tb_array;

typedef struct stat_array {
    int* l;
    int* u;
    int* f;
    int* d;
    bool** d_array;
} stat_array;

typedef struct stat_holder {
    stat_array *stats;
    int size;
} stat_holder;

void loadTables(tb_array** t_a, stat_holder** sh);
void destroyTables(tb_array* tb);
void destroyRelation(relation* rel);
#endif
