#include <stdint.h>
/** Type definition for a tuple */
struct tuple;
struct relation;

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
    tuple *tuples;
    uint32_t num_tuples;
} relation;

typedef struct ord_relation {
    int32_t row_id;
    int32_t value;
}ord_relation;