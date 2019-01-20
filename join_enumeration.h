#ifndef JOIN_ENUMERATION_H
#define JOIN_ENUMERATION_H

struct BestTree;
struct node;

typedef struct node {
    pred_list* q;
} node;

typedef struct BestTree {

} BestTree;

BestTree join_enumeration(Queue* , stat_holder* );
BestTree createJoinTree(int );
BestTree createBestTree();
Cost createHashCost();

void insert(int, char *);
int hashing(char *);
int cost(stat_holder *);
int factorial(int );
void addToBestTree(BestTree , pred_list);

#endif
