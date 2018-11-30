#include "queue.h"

Queue* createQueue(unsigned capacity) 
{ 
	Queue* queue = malloc(sizeof(Queue)); 
	queue->capacity = capacity; 
	queue->front = queue->size = 0; 
	queue->rear = capacity - 1; // This is important, see the enqueue 
	queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
	return queue; 
} 

int isFull(Queue* queue) 
{ return (queue->size == queue->capacity); } 

// Queue is empty when size is 0 
int isEmpty(Queue* queue) 
{ return (queue->size == 0); } 

void enqueue(Queue* queue, pred_list* item) 
{ 
	if (isFull(queue)) 
		return; 
	queue->rear = (queue->rear + 1)%queue->capacity; 
	queue->array[queue->rear] = item; 
	queue->size = queue->size + 1; 
	printf("%d enqueued to queue\n", item); 
} 

pred_list* dequeue(Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	int item = queue->array[queue->front]; 
	queue->front = (queue->front + 1)%queue->capacity; 
	queue->size = queue->size - 1; 
	return item; 
} 

// Function to get front of queue 
pred_list* front(Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	return queue->array[queue->front]; 
} 

// Function to get rear of queue 
pred_list* rear(Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	return queue->array[queue->rear]; 
} 
 
Queue* makeInstructionQueue(pred_list* ls, int tot_j, int tot_f){ 
    // we must check for table AND COLUMN!!!
    pred_list* marked_j[tot_j];
    pred_list* marked_f[tot_f];
    pred_list* temp = ls;
    Queue* q = createQueue(tot_f+tot_j);

    // run list of instruction and mark joins and filters
    int i=0, j=0;
    while(temp != NULL){
        // if its a join
        if(ls->op == 0){
            marked_j[i] = temp;
            i++;
        }
        // if its a filter
        else{
            marked_f[j] = temp;
            j++;
        }
        temp = temp->next;
    }

    // search for tables that take part in both join and filter
    // for every filter
    for(int j=0; j < tot_f; j++){

        if(marked_f[j] == NULL) continue;

        // search if it exists on joins
        for(int i=0; i<tot_j; i++){

            if(marked_j[i] == NULL) continue;

            // if found
            if(marked_f[j]->t1->table == marked_j[i]->t1->table){
                enqueue(q, marked_f[j]);
                marked_f[j] = NULL;

                // check if the second table in join has a filter
                for(int y=j+1; y<tot_f; y++){
                    if(marked_f[y] == NULL) continue;

                    if(marked_j[i]->t2->table == marked_f[y]->t1->table){
                        enqueue(q, marked_f[y]);
                        marked_f[y] = NULL;
                        break;
                    }
                }
                enqueue(q, marked_j[i]);
                marked_j[i] = NULL;
                break;
            }
            else if(marked_f[j]->t1->table == marked_j[i]->t2->table){
                enqueue(q, marked_f[j]);
                marked_f[j] = NULL;

                // check if the second table in join has a filter
                for(int y=j+1; y<tot_f; y++){
                    if(marked_f[y] == NULL) continue;

                    if(marked_j[i]->t1->table == marked_f[y]->t1->table){
                        enqueue(q, marked_f[y]);
                        marked_f[y] = NULL;
                        break;
                    }
                }
                enqueue(q, marked_j[i]);
                marked_j[i] = NULL;
                break;
            }
        }
        marked_f[j] = NULL;
    }
    return q;
}

int check_Eq(data* d1, data* d2){

}
