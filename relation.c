#include "relation.h"

tb_array* loadTables(char* path, tb_array** t_a){

    // get the initil file and start reading it
    char* line = NULL;
    char buf[1024];

    printf("Going to open : %s\n", path);
    FILE* init = fopen(path, "r");
    if(init == NULL) perror("init file error");
    
    char c;
    int lines=0;
    while((c = getc(init)) != EOF) 
        if(c == '\n') lines++;

    fclose(init);
    init = NULL;
    init = fopen(path, "r");
    if(init == NULL) perror("init file error");

    (*t_a) = malloc(sizeof(tb_array));
    (*t_a)->tb = malloc(lines*sizeof(st_table*));
    (*t_a)->size = lines;

    int i = 0;
    // for each relation file in the initial
    while(fgets(buf, sizeof(buf), init) != NULL){
        printf("starting\n");
        buf[strlen(buf) - 1] = '\0';

        // make the path
        char* temp = malloc(strlen(path)+strlen(buf));
        strcpy(temp, path);
        while(temp[strlen(temp)-1] != '/') temp[strlen(temp)-1] = '\0'; 
        strcat(temp, buf);

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
        int64_t* addr = NULL;
        if((addr=mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0u)) == MAP_FAILED){
            perror("cannot map file\n");
            exit(-1);
        }

        if(sb.st_size < 16) perror("relation file does not contain a valid header");
        uint64_t size = *addr;
        printf("size: %ld\n", size);
        addr+=sizeof(size);

        (*t_a)->tb[i] = malloc(sizeof(st_table));
        (*t_a)->tb[i]->rows = size;
        printf("%d\n", (*t_a)->tb[i]->rows);
        (*t_a)->tb[i]->col = malloc(size*sizeof(int64_t*));

        printf("2\n");

        size_t numColumns = *addr;
        addr+=sizeof(numColumns);

        for (unsigned j=0;j<numColumns;++j) {
            (*t_a)->tb[i]->col[j] = addr;
            addr+=size*sizeof(uint64_t);
        }

        free(temp);
        i++;
        printf("ending\n");
    }

    fclose(init);
    if(line) free(line);

    return (*t_a);
}

void destroyTables(tb_array* tb){
    for(int i=0; i < tb->size; i++){
        free(tb->tb[i]->col);
        free(tb->tb[i]);
    }
    free(tb->tb);
    free(tb);   
}
