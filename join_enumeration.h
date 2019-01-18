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
BestTree createJoinTree();
//BestTree createBestTree();
#endif
void insert(char *);
