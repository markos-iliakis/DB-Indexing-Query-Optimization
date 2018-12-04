#include "result.h"

int main(int argc, char** argv){

    srand(time(NULL));

    // get table paths from stdin and store them
    tb_array* tb = NULL;
    loadTables(&tb);
    printf("loadTables ok\n");

    //create indexes for every table and column
    indexes_array* indexes = createIndexes(tb);
    printf("createIndexes ok\n");

    destroyTables(tb);
    destroyIndexes(indexes);

    return 0;
}

// bash ./start.sh ./submission/workloads/small/small.init | ./main