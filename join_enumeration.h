#ifndef JOIN_ENUMERATION_H
#define JOIN_ENUMERATION_H

struct BestTree;
struct node;

typedef struct node {
    char* name;
    struct node* next;
} node;

typedef struct BestTree {

} BestTree;

BestTree join_enumeration();
BestTree createJoinTree(int );
//BestTree createBestTree();
#endif
void insert(int, char *);
int hashing(char *);
int cost(stat_holder *);
