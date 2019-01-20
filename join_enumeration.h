#ifndef JOIN_ENUMERATION_H
#define JOIN_ENUMERATION_H

struct BestTree;
struct Cost;

typedef struct BestTree {
    struct data* rel;
} BestTree;

typedef struct Cost {
    int
} Cost;

BestTree join_enumeration();
BestTree createJoinTree();
BestTree createBestTree();
Cost createHashCost();

void insert();
int hashing();
int cost();
int factorial(int );
void addToBestTree();

#endif
