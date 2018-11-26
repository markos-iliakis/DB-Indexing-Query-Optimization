#include "relation.h"

tb_array* loadTables(tb_array** t_a){

    // get the initil file and start reading it
    char* line = NULL;
    char buf[1024];

    // printf("Going to open : %s\n", path);
    // FILE* init = fopen(path, "r");
    // if(init == NULL) perror("init file error");
    
    // char c;
    int lines=0;
    // while((c = getc(init)) != EOF) 
        // if(c == '\n') lines++;

    // fclose(init);
    // init = NULL;
    // init = fopen(path, "r");
    // if(init == NULL) perror("init file error");

    char lines_str[10];
    scanf("%s\n", lines_str);
    lines = atoi(lines_str);
    printf("lines: %d\n", lines);

    (*t_a) = malloc(sizeof(tb_array));
    (*t_a)->tb = malloc(lines*sizeof(st_table*));
    (*t_a)->size = lines;

    // for each relation file in the initial
    for(int i=0; i<14; i++){
        // printf("starting\n");
        // buf[strlen(buf) - 1] = '\0';

        // // make the path
        // char* temp = malloc(strlen(path)+strlen(buf));
        // strcpy(temp, path);
        // while(temp[strlen(temp)-1] != '/') temp[strlen(temp)-1] = '\0'; 
        // strcat(temp, buf);

        scanf("%s\n", buf);

        // open the binary
        printf("Going to open : %s\n", buf);
        int fd = open(buf, O_RDONLY);
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

        // free(temp);
        printf("ending\n");
    }

    // fclose(init);
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
