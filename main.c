#include "result.h"

int main(int argc, char** argv){

    srand(time(NULL));

    // get table paths from stdin and store them
    tb_array* tb = NULL;
    printf("Loading Tables\n");
    loadTables(&tb);
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