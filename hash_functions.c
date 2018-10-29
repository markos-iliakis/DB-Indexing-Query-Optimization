#include "hash_functions.h"

int h1(int num){
    return atoi(decimal_to_binary(num)) % 1000;
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
