#include "hash_functions.h"

int h1(int num){
    char* str = decimal_to_binary(num);
    int ret = atoi(str) % 100000000;
    free(str);
    return ret;
}

char *decimal_to_binary(int n){
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(32+1);

   if (pointer == NULL)
      exit(2);

   for (c = 31 ; c >= 0 ; c--){
      d = n >> c;

      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';

   return  pointer;
}

int h2(int value){
    return value%101;
}

// function to transform initial arrays to hash-value/row-id array
tuple** makeHashIdArray(int64_t** x_array, int xdimen, int colNo){
    tuple **x_tuple = malloc(xdimen * sizeof(tuple *));

    for (int i = 0; i < xdimen; i++) {
        x_tuple[i] = malloc(sizeof(tuple));
        x_tuple[i]->key = h1(x_array[colNo][i]);
        x_tuple[i]->payload = i;
        x_tuple[i]->value = x_array[colNo][i];
    }
    return x_tuple;
}
