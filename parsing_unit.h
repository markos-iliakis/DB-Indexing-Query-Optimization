#ifndef PARSING_UNIT_H
#define PARSING_UNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queries;
struct batch;
struct instruction;
struct parsed_instruction;
struct pred_list;
struct proj_list;
struct data;

typedef struct queries {
    int num;
    struct batch *head;
} queries;

typedef struct batch {
    int num;
    struct batch *next;
    struct instruction *head;
} batch;

typedef struct instruction {
    char *rel;
    char *pred;
    char *proj;
    struct instruction *next;
} instruction;

typedef struct parsed_instruction {
    int *arrays;
    struct pred_list *pl;
    struct proj_list *prl;
    struct parsed_instruction *next;
} parsed_instruction;

typedef struct pred_list {
    int op; // 0 if = for join, 1 if < ,2 if > and 3 if = for number filter
    struct data *t1;
    struct data *t2; // for other table or to hold number
    struct pred_list *next;
} pred_list;

typedef struct data {
    int table;
    int appearance;
    // int a_table; // real number of table
    int column; // -1 if op is > or <
} data;

typedef struct proj_list {
    struct data *t;
    struct proj_list *next;
} proj_list;

extern int t;

void print(queries *root);
void printQuery(parsed_instruction* pi);
int findAppearances(int *arrays, int array_num);
#endif