#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include "parsing_unit.h"

typedef struct Queue { 
	int front, rear, size; 
	unsigned capacity; 
	pred_list** array; 
}Queue; 

Queue* createQueue(unsigned capacity);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, pred_list* item);
pred_list* dequeue(Queue* queue);
pred_list* front(Queue* queue);
pred_list* rear(Queue* queue);

int check_Eq(data* d1, data* d2);
Queue* makeInstructionQueue(pred_list* ls, int tot_j, int tot_f);