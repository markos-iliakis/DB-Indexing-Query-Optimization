#include "result.h"

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t done_jobs_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;
int t = 1;
// sem_t finished_jobs;

jobScheduler* jSched;

int main(int argc, char** argv){

    // sem_init(&finished_jobs, 0, -);
    srand(time(NULL));

    // initialize job scheduler and threads
    jobScheduler_Init(&jSched);

    // get table paths from stdin and store them
    tb_array* tb = NULL;
    stat_holder* sh = NULL;

    // fprintf(stderr, "Loading Tables\n");
    loadTables(&tb, &sh);
    // loadTables(&tb);
    // loadTestTables(&tb, 8, 8, 8);
    fprintf(stderr, "\nTables Loaded\n");

    // create indexes for every table and column
    fprintf(stderr, "\nCreating Indexes\n");
    indexes_array* indexes = createIndexes(tb);
    fprintf(stderr, "\nIndexes Created\n");

    // get and serve the queries
    fprintf(stderr, "\nExecuting Queries\n");
    parseInstuctions(indexes);
    fprintf(stderr, "\nQueries Run\n");
    //parseInstuctions(indexes, sh);

    destroyTables(tb);
    destroyIndexes(indexes);
    //destroyStats(sh);

    return 0;
}

// bash ./start.sh ./submission/workloads/small/small.init | ./main
// ./submission/runTestharness.sh
