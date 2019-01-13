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

void Barrier(int to_be_done){
    // lock access of queue
    pthread_mutex_lock(&mutex2);

    // Check if queue has at least 1 element 
    while(done_jobs < to_be_done){
        pthread_cond_wait(&can_produce, &mutex2); // must use semaphore tha starts with -number of jobs to be done
        // pthread_mutex_lock(&done_jobs_mutex);
        // done_jobs++;
        // pthread_mutex_unlock(&done_jobs_mutex);
        // pthread_mutex_lock(&print_mutex);
        // fprintf(stderr, "done jobs %d\n", done_jobs);
        // pthread_mutex_unlock(&print_mutex);
    } 
    // Get the mutex unlocked 
    pthread_mutex_unlock(&mutex2); 
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

        // Get the mutex unlocked 
        pthread_mutex_unlock(&mutex); 

        // run the function
        (*(j->function))(j->argument);

        // pthread_mutex_lock(&print_mutex);
        // fprintf(stderr, "A job finished\n");
        // pthread_mutex_unlock(&print_mutex);

        
        pthread_mutex_lock(&done_jobs_mutex);
        done_jobs++;
        pthread_mutex_unlock(&done_jobs_mutex);
        pthread_mutex_lock(&mutex2);
        pthread_cond_signal(&can_produce);
        pthread_mutex_unlock(&mutex2);
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
    return NULL;
}

histogram* createParallelHistogram(int tot_num, relation* rel){
    int inc = tot_num/THR_NUM;
    int line_start = 0;
    int line_stop = inc;

    Job** jobs = malloc(THR_NUM*sizeof(Job*));
    done_jobs = 0; 

    // give the jobs to jobSchedler
    for(int i=0; i < THR_NUM; i++){
    
        // make the argument
        histArgs* hArg = histArgsInit(line_start, line_stop, rel);

        // make the job
        jobInit(createHistogram, hArg, &(jobs[i]));

        // add job to schedulers
        Schedule(jobs[i]);

        line_start = line_stop;
        line_stop += inc;
        if(i+2 == THR_NUM) line_stop = tot_num;
    }

    // wait for all histograms to finish
    Barrier(THR_NUM);
    // pthread_mutex_lock(&print_mutex);
    // fprintf(stderr, "All jobs finished\n");
    // pthread_mutex_unlock(&print_mutex);
    // getchar();

    histogram* hist = NULL;
    // unite histograms of all threads
    for(int i=0; i < THR_NUM; i++){
        histogram* temp = ((histArgs*)(jobs[i]->argument))->hist;
        
        // run through sublist of one thread
        while(temp != NULL){

            histogram* temp2 = hist;
            histogram* ret = NULL;

            // check if exist in main histogram
            if((ret = searchHistogram(temp2, temp->value)) != NULL) addFreq(ret, temp->freq);
            else addHistogram(&hist, temp->value, temp->freq);
            temp = temp->next;
        }
    }

    return hist;
}

ord_relation** createParallelReaorderedArray(sum **psum, int size, relation *rel, int xdimen){
    
    // get the required space
    ord_relation** new_array = malloc(xdimen * sizeof(ord_relation *));
    for (int i = 0; i < xdimen; i++) new_array[i] = malloc(sizeof(ord_relation));

    Job** jobs = malloc(size*sizeof(Job*)); 
    done_jobs = 0;

    // give the jobs to jobSchedler
    for(int i=1; i <= size; i++){

        int line_start = psum[i-1]->index;
        int line_stop;
        if(i == size) line_stop = xdimen;
        else line_stop = psum[i]->index;

        // make the argument
        ordArgs* oArg = ordArgsInit(line_start, line_stop, xdimen, psum[i-1]->hashed_key, rel, new_array);

        // make the job
        jobInit(createPartialReorderedArray, oArg, &(jobs[i-1]));

        // add job to scheduler
        // pthread_mutex_lock(&print_mutex);
        // printf("[main] adding a job %d->%d\n", oArg->lines_start, oArg->lines_stop);
        // pthread_mutex_unlock(&print_mutex);
        Schedule(jobs[i-1]);
    }

    // pthread_mutex_lock(&print_mutex);
    // printf("[main] waiting all threads to finish\n");
    // pthread_mutex_unlock(&print_mutex);

    // wait for all subarrays to finish
    Barrier(size);

    for(int i=0; i<size-1; i++){
        psum[i]->index = psum[i+1]->index;
    }
    psum[size-1]->index = xdimen;

    return new_array;
}

void* createPartialReorderedArray(ordArgs* oArg){
    int ind = oArg->lines_start;
    for(int i=0; i<oArg->total_lines; i++){
        if(oArg->rel->tuples[i]->key == oArg->search_key){
            oArg->ord_rel[ind]->row_id = oArg->rel->tuples[i]->payload;
            oArg->ord_rel[ind]->value = oArg->rel->tuples[i]->value;
            ind++;
            if(ind > oArg->lines_stop) break; 
        }
    }

    // pthread_mutex_lock(&print_mutex);
    // printf("[Thread] %d->%d\n", oArg->lines_start, oArg->lines_stop);
    // pthread_mutex_unlock(&print_mutex);
    return NULL;
}

ordArgs* ordArgsInit(int line_start, int line_stop, int total_lines, int search_key, relation* rel, ord_relation** ord_rel){
    ordArgs* oArg = malloc(sizeof(ordArgs));
    oArg->lines_start = line_start;
    oArg->lines_stop = line_stop;
    oArg->total_lines = total_lines;
    oArg->search_key = search_key;
    oArg->rel = rel;
    oArg->ord_rel = ord_rel;
    return oArg;
}

histArgs* histArgsInit(int line_start, int line_stop, relation *rel){
    histArgs* hArg = malloc(sizeof(histArgs));
    hArg->lines_start = line_start;
    hArg->lines_stop = line_stop;
    hArg->rel = rel;
    hArg->hist = NULL;
    return hArg;
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

void perror2(const char* s, int err){
    fprintf(stderr, "%s: %s\n", s, strerror(err));
    exit(1);
}