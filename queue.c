#include "queue.h"

Queue* createQueue(unsigned capacity){ 
	Queue* queue = malloc(sizeof(Queue)); 
	queue->capacity = capacity; 
	queue->front = queue->size = 0; 
	queue->rear = capacity - 1; // This is important, see the enqueue 
	queue->array = malloc(queue->capacity * sizeof(pred_list*)); 
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
	// printf("%d enqueued to queue\n", item); 
} 

pred_list* dequeue(Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return NULL; 
	pred_list* item = queue->array[queue->front]; 
	queue->front = (queue->front + 1)%queue->capacity; 
	queue->size = queue->size - 1; 
	return item; 
} 

// Function to get front of queue 
pred_list* front(Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return NULL; 
	return queue->array[queue->front]; 
} 

// Function to get rear of queue 
pred_list* rear(Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return NULL; 
	return queue->array[queue->rear]; 
} 
 
Queue* makeInstructionQueue(pred_list* ls, int tot_j, int tot_f){
    pred_list* marked_j[tot_j];
    pred_list* marked_f[tot_f];
    pred_list* temp = ls;
    Queue* q = createQueue(tot_f+tot_j);
    printf("totj %d totf %d\n", tot_j, tot_f);

    // run list of instruction and mark joins and filters
    int i=0, j=0;
    while(temp != NULL){
        // printf("currently looking node with op %d and table1 %d\n", temp->op, temp->t1->table);
        // if its a join
        if(temp->op == 0){
            marked_j[i] = temp;
            printf("marked join %d-%d\n", marked_j[i]->t1->table, marked_j[i]->t2->table);
            i++;
        }
        // if its a filter
        else{
            marked_f[j] = temp;
            printf("marked filter %d-%d\n", marked_f[j]->t1->table, marked_f[j]->t2->table);
            j++;
        }
        temp = temp->next;
    }
    printf("joins and filters marked\n\n");

    // search for tables that take part in both join and filter
    // for every filter
    for(int j=0; j < tot_f; j++){

        if(marked_f[j] == NULL) continue;
        printf("checking (table)%d (symbol)%d (num)%d\n", marked_f[j]->t1->table, marked_f[j]->op, marked_f[j]->t2->table);
        // search if it exists on joins
        for(int i=0; i<tot_j; i++){

            if(marked_j[i] == NULL) continue;
            printf("checking join: %d-%d\n", marked_j[i]->t1->table, marked_j[i]->t2->table);
            // if found on the table 1 of join
            if(check_Eq(marked_f[j]->t1, marked_j[i]->t1)){
                printf("f-1 match found\n");
                enqueue(q, marked_f[j]);
                marked_f[j] = NULL;

                // check if the second table in join has a filter
                for(int y=j+1; y<tot_f; y++){
                    if(marked_f[y] == NULL) continue;

                    if(check_Eq(marked_j[i]->t2, marked_f[y]->t1)){
                        enqueue(q, marked_f[y]);
                        marked_f[y] = NULL;
                        break;
                    }
                }
                enqueue(q, marked_j[i]);
                marked_j[i] = NULL;
                break;
            }
            // if found on the table 2 of join
            else if(check_Eq(marked_f[j]->t1, marked_j[i]->t2)){
                printf("f-2 match found\n");
                enqueue(q, marked_f[j]);
                marked_f[j] = NULL;

                // check if the second table in join has a filter
                for(int y=j+1; y<tot_f; y++){
                    if(marked_f[y] == NULL) continue;

                    if(check_Eq(marked_j[i]->t1, marked_f[y]->t1)){
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
    printf("connected joins and filters added to queue\n");

	// insert the remaining joins and filters in queue
	for(int i=0; i<tot_j; i++){
		if(marked_j[i] == NULL) continue;
		enqueue(q, marked_j[i]);
	}

	for(int j=0; j<tot_f; j++){
		if(marked_f[j] == NULL) continue;
		enqueue(q, marked_f[j]);
	}
    printf("remaining joins and filters added to queue\n");

    return q;
}

int check_Eq(data* d1, data* d2){
	// if(d1->table == d2->table && d1->column == d2->column) return 1;
    if(d1->table == d2->table) return 1;
	else return 0;
}
