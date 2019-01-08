#include "job_scheduler.h"

jobScheduler* jobScheduler_Init(){
    jobScheduler* js = malloc(sizeof(jobScheduler));
    js->pool = thr_pool_Init(THR_NUM);
    queueInit(js->queue, sizeof(Job*));
}

void Schedule(Job* job){
    // lock to access the shared queue
    pthread_mutex_lock(&mutex);

    // add to queue
    enqueue3(jSched->queue, job);

    // broadcast data in queue
    pthread_cond_broadcast(&dataNotProduced);

    // unlock access
    pthread_mutex_unlock(&mutex);
}

thr_pool* thr_pool_Init(int num){
    int err;
    thr_pool* pool = malloc(sizeof(thr_pool));
    pool->thr = malloc(num * sizeof(pthread_t*));

    for(int i=0; i < num; i++)
        if((err = pthread_create(&(pool->thr[i]), NULL, threadFunction, NULL)) != 0) perror2("pthread_create", err);
    

    pool->thr_num = num;
    return pool;
}

Job* jobInit(void* function, void* arg){
    Job* job = malloc(sizeof(Job));
    job->function = function;
    job->argument = arg;
    return job;
}

void Barrier(){
    // initialize barrier
    pthread_barrier_init(&barrier, NULL, THR_NUM);
    // wait for it ...
    pthread_barrier_wait(&barrier);
    // destroy barrier
    pthread_barrier_destroy(&barrier);
}

histArgs* histArgsInit(int line_start, int line_stop, relation *rel){
    histArgs* hArg = malloc(sizeof(histArgs));
    hArg->lines_start = line_start;
    hArg->lines_stop = line_stop;
    hArg->rel = rel;
    hArg->hist = NULL;
    return hArg;
}

void* threadFunction(){
    while (1) { 
  
        // lock access of queue
        pthread_mutex_lock(&mutex);

        Job* j = malloc(sizeof(Job)); 
  
        // Check if queue has at least 1 element 
        if (jSched->queue->sizeOfQueue > 0) { 

            // Get the Job
            dequeue3(jSched->queue, j); 

            // pthread_cond_signal(&dataNotConsumed); 
        }   
        else {  
            // If some other thread is exectuing, wait
            pthread_cond_wait(&dataNotProduced, &mutex); 
        } 
  
        // Get the mutex unlocked 
        pthread_mutex_unlock(&mutex); 

        // run the function
        (*(j->function))(j->argument);
    } 
}

void perror2(const char* s, int err){
    fprintf(stderr, "%s: %s\n", s, strerror(err));
    exit(1);
}