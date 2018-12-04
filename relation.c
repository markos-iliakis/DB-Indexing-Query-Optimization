#include "relation.h"

void loadTables(tb_array** t_a){

    char* line = NULL;
    char buf[1024];
    int lines=0;

    // read the number of tables to be read
    char lines_str[10];
    scanf("%s\n", lines_str);
    lines = atoi(lines_str);
    // printf("tables: %d\n", lines);

    (*t_a) = malloc(sizeof(tb_array));
    (*t_a)->tb = malloc(lines*sizeof(st_table*));
    (*t_a)->size = lines;

    // for each table file in the initial
    for(int i=0; i<14; i++){

        // read the table from the script
        scanf("%s\n", buf);

        // open the binary
        // printf("Going to open : %s\n", buf);
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
        addr+=sizeof(size);

        (*t_a)->tb[i] = malloc(sizeof(st_table));
        (*t_a)->tb[i]->rows = size;
        (*t_a)->tb[i]->col = malloc(size*sizeof(int64_t*));

        size_t numColumns = *addr;
        addr+=sizeof(numColumns);

        for (unsigned j=0;j<numColumns;++j) {
            (*t_a)->tb[i]->col[j] = addr;
            addr+=size*sizeof(uint64_t);
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
