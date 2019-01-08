#include <stdlib.h>
#include <string.h>

#ifndef QUEUE3_H
#define QUEUE3_H

typedef struct Node
{
  void *data;
  struct Node *next;
}node;

typedef struct QueueList
{
    int sizeOfQueue;
    size_t memSize;
    node *head;
    node *tail;
}Queue3;

void queueInit(Queue3 *q, size_t memSize);
int enqueue3(Queue3 *, const void *);
void dequeue3(Queue3 *, void *);
void queuePeek(Queue3 *, void *);
void clearQueue(Queue3 *);
int getQueueSize(Queue3 *);
#endif