#include "result.h"

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  
pthread_cond_t can_produce = PTHREAD_COND_INITIALIZER; 
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;

jobScheduler* jSched;

int main(int argc, char** argv){

    srand(time(NULL));

    // initialize job scheduler and threads
    jobScheduler_Init(&jSched);

    // get table paths from stdin and store them
    tb_array* tb = NULL;
    printf("Loading Tables\n");
    loadTables(&tb);
    // loadTestTables(&tb, 1, 8, 3);
    printf("\nTables Loaded\n");
    
    // create indexes for every table and column
    printf("\nCreating Indexes\n");
    indexes_array* indexes = createIndexes(tb);
    printf("\nIndexes Created\n");

    // get and serve the queries
    parseInstuctions(indexes);

    destroyTables(tb);
    destroyIndexes(indexes);

    return 0;
}

// bash ./start.sh ./submission/workloads/small/small.init | ./main