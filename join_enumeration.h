#ifndef JOIN_ENUMERATION_H
#define JOIN_ENUMERATION_H

#include <math.h>

struct BestTree;

typedef struct BestTree {
    int* jeT;
    int cost;
} BestTree;


BestTree join_enumeration();
int hashing(int* , int );
int factorial(int );
int cost(int , data* , data* , new_stats* , new_stats* );
int connected(Queue* , int* , int , int );
int r_in_s(int* , int , int );

#endif
