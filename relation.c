#include "relation.h"

relation** loadRelations(char* path){

    // get the initil file and start reading it
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    printf("Going to open : %s\n", path);
    FILE* init = fopen(path, "r");
    if(init == NULL) perror("init file error");

    relation** rel = malloc(14*sizeof(relation*));   //MUST DO IT DYNAMICALLY WITH ANOTHERSTRUCT OR REALLOCS
    int i = 0;

    // for each relation file in the initial
    while((read = getline(&line, &len, init)) != -1){
        
        // make the path
        char* temp = malloc(sizeof(path)+sizeof(line));
        strcpy(temp, path);
        while(temp[strlen(temp)-1] != '/') temp[strlen(temp)-1] = '\0'; 
        strcat(temp, line);
        temp[strlen(temp)-1] = '\0';

        // open the binary
        printf("Going to open : %s\n", temp);
        int fd = open(temp, O_RDONLY);
        if(fd == -1) {
            perror("File not Found!");
            exit(-1);
        }

        // Obtain file size
        struct stat sb;
        if (fstat(fd,&sb)==-1) {
            perror("Wrong size!");
            exit(-1);
        }

        // add to memmory
        int* addr = NULL;
        addr=mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0u);

        if(sb.st_size < 16) perror("relation file does not contain a valid header");
        uint64_t size = *addr;
        addr+=sizeof(size);
        printf("%ld\n", size);

        rel[i] = malloc(sizeof(relation));
        rel[i]->num_tuples = size;
        rel[i]->tuples = malloc(size*sizeof(tuple));

        size_t numColumns = *addr;
        addr+=sizeof(size_t);

        for (unsigned i=0;i<numColumns;++i) {

            addr+=size*sizeof(uint64_t);
        }

        free(temp);
        i++;
    }

    fclose(init);
    if(line) free(line);

    return 0;
}
