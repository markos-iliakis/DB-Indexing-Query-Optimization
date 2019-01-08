#ifndef JOB_SCHEDULER_H
#define JOB_SCHEDULER_H

#include "result.h"
#include <pthread.h>
#include <semaphore.h>
#include <dirent.h>
#include "queue3.h"

#define THR_NUM 8

extern pthread_mutex_t mutex;  
extern pthread_cond_t dataNotProduced; 
extern pthread_cond_t dataNotConsumed;
extern pthread_barrier_t barrier;

typedef struct thr_pool{
    pthread_t* thr;
    int thr_num; 
}thr_pool;

typedef struct histArgs{
    int lines_start;
    int lines_stop;
    relation* rel;
    histogram* hist;
}histArgs;

typedef struct Job{
    void (*function)(void* );
    void* argument;
}Job;

typedef struct jobScheduler{
    thr_pool* pool;
    Queue3* queue;
}jobScheduler;

extern jobScheduler* jSched;

jobScheduler* jobScheduler_Init();
void Schedule(Job* job);
void Barrier();

thr_pool* thr_pool_Init(int num);
histArgs* histArgsInit(int line_start, int line_stop, relation *rel);

Job* jobInit(void* function, void* arg);

void* threadFunction();
void perror2(const char* s, int err);
#endif