#include <pthread.h>
#include <semaphore.h>
#include <dirent.h>
#include "queue3.h"
#include "histogram.h"
#include <unistd.h>

#ifndef JOB_SCHEDULER_H
#define JOB_SCHEDULER_H

#define THR_NUM 8

extern pthread_mutex_t print_mutex;
extern pthread_mutex_t mutex;  
extern pthread_cond_t can_produce; 
extern pthread_cond_t can_consume;

typedef struct thr_pool{
    pthread_t* thr;
    int thr_num;
}thr_pool;

typedef struct Job{
    void (*function)(void* );
    void* argument;
}Job;

typedef struct jobScheduler{
    thr_pool* pool;
    Queue3* queue;
}jobScheduler;

// struct for passing histogram argument to threads
typedef struct histArgs{
    int lines_start;
    int lines_stop;
    relation* rel;
    histogram* hist;
}histArgs;

extern jobScheduler* jSched;

void jobScheduler_Init(jobScheduler** jSched);
void Schedule(Job* job);
void Barrier();

thr_pool* thr_pool_Init(int num);
histArgs* histArgsInit(int line_start, int line_stop, relation *rel);

void jobInit(void* function, void* arg, Job** job);

void* threadFunction();
void perror2(const char* s, int err);

histogram* createParallelHistogram(int tot_num, relation* rel);

void printQueue3(Queue3* q);
void* createHistogram(histArgs* histAr);
#endif