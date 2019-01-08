#include "relation.h"

#ifndef HASH_FUNCTIONS_
#define HASH_FUNCTIONS_

int h1(int num);
char* decimal_to_binary(int n);
int h2(int value);
tuple** makeHashIdArray(int64_t** x_array, int xdimen, int col_no);

#endif
