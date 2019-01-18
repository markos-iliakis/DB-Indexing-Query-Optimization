#include "relation.h"

//void loadTables(tb_array** t_a, stat_holder** sh){
void loadTables(tb_array** t_a){

    char* line = NULL;
    int lines=14;

    // read the number of tables to be read
    // char lines_str[10];
    // if(scanf("%s\n", lines_str) < 0) exit(-2);
    // lines = atoi(lines_str);
    // printf("tables: %d\n", lines);

    (*t_a) = malloc(sizeof(tb_array));
    (*t_a)->tb = malloc(lines*sizeof(st_table*));
    (*t_a)->size = lines;

    (*sh) = malloc(sizeof());
    

    // for each table file in the initial
    for(int i=0; i<lines; i++){

        // char cwd[1024];
        // getcwd(cwd, sizeof(cwd));
        // fprintf(stderr, "Current working dir: %s\n", cwd);

        char* buf = malloc(5*sizeof(char));

        // read the table from the script
        if(scanf("%s\n", buf) < 0) exit(-2);

        // char buf2 [1024];
        // strcpy(buf2, "./submission/workloads/small/\0");
        // strcat(buf2, buf);

        // open the binary
        // fprintf(stderr, "Going to open : %s\n", buf);
        int fd = open(buf, O_RDONLY);
        if(fd == -1) {
            perror("File not Found!");
            exit(-1);
        }

        free(buf);

        // Obtain file size
        struct stat sb;
        if (fstat(fd,&sb)==-1) {
            perror("Wrong size!");
            exit(-1);
        }

        // add to memmory
        int64_t* addr = NULL;
        int offset = 0;
        if((addr=mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED){
            perror("cannot map file\n");
            exit(-1);
        }

        if(sb.st_size < 16) perror("relation file does not contain a valid header");

        // first element of header
        uint64_t size = *addr;
        offset++;

        // second element of header
        uint64_t numColumns = *(addr+offset);
        offset++;

        (*t_a)->tb[i] = malloc(sizeof(st_table));
        (*t_a)->tb[i]->rowNum = size;
        (*t_a)->tb[i]->colNum = numColumns;
        (*t_a)->tb[i]->col = malloc(numColumns*sizeof(int64_t*));

        for(int j=0; j < numColumns; j++){
            (*t_a)-> tb[i]->col[j] = addr+offset;
            offset += size;
        }
    }

    if(line) free(line);
}

void destroyTables(tb_array* tb){
    for(int i=0; i < tb->size; i++){
        free(tb->tb[i]->col);
        free(tb->tb[i]);
    }
    free(tb->tb);
    free(tb);
}

void destroyRelation(relation* rel){

    for(int i=0; i < rel->num_tuples; i++){
        free(rel->tuples[i]);
    }
    free(rel->tuples);

    free(rel);
}
