#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

/** Type definition for a tuple */
struct tuple;
struct relation;
struct result;

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

typedef struct st_table{
    int rows;
    int64_t** col;
}st_table;

typedef struct tb_array{
    st_table** tb;
    int size;
}tb_array;

tb_array* loadTables(tb_array** t_a);
void destroyTables(tb_array* tb);