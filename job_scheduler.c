#include "job_scheduler.h"

void jobScheduler_Init(jobScheduler** jSched){
    *jSched = malloc(sizeof(jobScheduler));
    queueInit(&((*jSched)->queue), sizeof(Job));
    (*jSched)->pool = thr_pool_Init(THR_NUM);
}

void Schedule(Job* job){
    // lock to access the shared queue
    pthread_mutex_lock(&mutex);

    // add to queue
    enqueue3(jSched->queue, job);
    // printQueue3(jSched->queue);

    // broadcast data in queue
    pthread_cond_broadcast(&can_consume);

    // unlock access
    pthread_mutex_unlock(&mutex);
}

thr_pool* thr_pool_Init(int num){
    int err;
    thr_pool* pool = malloc(sizeof(thr_pool));
    pool->thr = malloc(num * sizeof(pthread_t*));
    pool->thr_num = num;
    for(int i=0; i < num; i++)
        if((err = pthread_create(&(pool->thr[i]), NULL, threadFunction, NULL)) != 0) perror2("pthread_create", err);
    
    return pool;
}

void jobInit(void* function, void* arg, Job** job){
    *job = malloc(sizeof(Job));
    (*job)->function = function;
    (*job)->argument = arg;
}

void Barrier(){
    // lock access of queue
        pthread_mutex_lock(&mutex);
  
        // Check if queue has at least 1 element 
        while(jSched->queue->sizeOfQueue > 0){
            pthread_cond_wait(&can_produce, &mutex);
        } 
        // Get the mutex unlocked 
        pthread_mutex_unlock(&mutex); 
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
        while(jSched->queue->sizeOfQueue <= 0){
            pthread_cond_wait(&can_consume, &mutex);
        } 

        // Get the Job
        dequeue3(jSched->queue, j);
        // printQueue3(jSched->queue);
        pthread_mutex_lock(&print_mutex); 
        printf("[thread %ld] %d->%d\n", pthread_self(), ((histArgs*)(j->argument))->lines_start, ((histArgs*)(j->argument))->lines_stop);
        pthread_mutex_unlock(&print_mutex);

        // Get the mutex unlocked 
        pthread_mutex_unlock(&mutex); 

        // run the function
        (*(j->function))(j->argument);

        pthread_cond_signal(&can_produce);
    } 
}

void* createHistogram(histArgs* histAr){
    
    for (int i = histAr->lines_start; i < histAr->lines_stop; i++) {
        histogram *temp = searchHistogram(histAr->hist, histAr->rel->tuples[i]->key);
        if (temp == NULL)
            addHistogram(&(histAr->hist), histAr->rel->tuples[i]->key, 1);
        else
            addFreq(temp, 1);
    }

    pthread_mutex_lock(&print_mutex);
    printf("%d->%d\n", histAr->lines_start, histAr->lines_stop);
    printHistogram(histAr->hist);
    pthread_mutex_unlock(&print_mutex);
    return NULL;
}

void perror2(const char* s, int err){
    fprintf(stderr, "%s: %s\n", s, strerror(err));
    exit(1);
}

histogram* createParallelHistogram(int tot_num, relation* rel){
    int inc = tot_num/THR_NUM;
    int line_start = 0;
    int line_stop = inc;

    Job** jobs = malloc(THR_NUM*sizeof(Job*)); 

    // give the jobs to jobSchedler
    for(int i=0; i < THR_NUM; i++){
    
        // make the argument
        histArgs* hArg = histArgsInit(line_start, line_stop, rel);

        // make the job
        jobInit(createHistogram, hArg, &(jobs[i]));

        // add job to scheduler
        pthread_mutex_lock(&print_mutex);
        printf("[main] adding a job %d->%d\n", hArg->lines_start, hArg->lines_stop);
        pthread_mutex_unlock(&print_mutex);
        Schedule(jobs[i]);

        line_start = line_stop;
        line_stop += inc;
    }

    pthread_mutex_lock(&print_mutex);
    printf("[main] waiting all threads to finish\n");
    pthread_mutex_unlock(&print_mutex);

    // wait for all histograms to finish
    Barrier();

    histogram* hist = NULL;

    printf("[main] start to unite histograms\n");
    // unite histograms of all threads
    for(int i=0; i < THR_NUM; i++){
        histogram* temp = ((histArgs*)(jobs[i]->argument))->hist;
        
        // run through sublist of one thread
        while(temp != NULL){

            histogram* temp2 = hist;
            histogram* ret = NULL;

            // check if exist in main histogram
            if((ret = searchHistogram(temp2, temp->value)) != NULL) addFreq(temp2, ret->freq);
            else addHistogram(&hist, temp->value, temp->freq);
            temp = temp->next;
        }
    }
    printHistogram(hist);

    return hist;
}

void printQueue3(Queue3* q){
    printf("\n");
    node* temp = q->head;
    for(int i=0; i<getQueueSize(q); i++){
        printf("%d->%d |", ((histArgs*)((Job*)(temp->data))->argument)->lines_start, ((histArgs*)((Job*)(temp->data))->argument)->lines_stop);
        temp = temp->next;
    }
    printf("\n\n");
}