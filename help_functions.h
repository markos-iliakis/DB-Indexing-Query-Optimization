#include "sum.h"

#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

// #include "job_scheduler.h"

#define DISTINCT 30

void printArrayTuple(int** x_array, tuple** x_tuple, int xdimen, int ydimen);
int** makeRandArray(int xdimen, int ydimen);

ord_relation** createReorderedarray(sum **psum, int size, relation *r_relation, int xdimen);
void printOrderedarray(ord_relation **array, int xdimen);

void destroyOrdArray(ord_relation** ord, int size);
void destroyRandArray(int** xarray, int xdimen);
#endif