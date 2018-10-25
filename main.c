#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "relation.h"

#define YDIMEN 4
#define XDIMEN 3
#define COMPARE 2

int main(void){

    srand(time(NULL));
    int **r_array = malloc(XDIMEN * sizeof(int *));
    for (int i = 0; i < XDIMEN; i++)
        r_array[i] = malloc(YDIMEN * sizeof(int));

    int **s_array = malloc(XDIMEN * sizeof(int *));
    for (int i = 0; i < XDIMEN; i++)
        s_array[j] = malloc(YDIMEN * sizeof(int));

    for (int i = 0; i < XDIMEN; i++) {
        for (int j = 0; j < YDIMEN; j++) {
            r_array[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < XDIMEN; i++) {
        for (int j = 0; j < YDIMEN; j++) {
            s_array[i][j] = rand() % 100;
        }
    }

    tuple *r_temp = malloc(XDIMEN * sizeof(tuple));
    tuple *s_temp = malloc(YDIMEN * sizeof(tuple));

    for (int i = 0; i < XDIMEN; i++) {
        r_temp->key = i+1;
        r_temp->payload = r_array[i][COMPARE];

        s_temp->key = i+1;
        s_temp->payload = s_array[i][COMPARE];
    }

    tuple *r_tuple = malloc(XDIMEN * sizeof(tuple));
    tuple *s_tuple = malloc(YDIMEN * sizeof(tuple));

    for (int i = 0; i < XDIMEN; i++) {
        r_tuple->key = i+1;
        r_tuple->payload = r_array[i][COMPARE];

        s_tuple->key = i+1;
        s_tuple->payload = s_array[i][COMPARE];
    }


    return 0;
}



int h1(int num){
    return atoi(decimal_to_binary(num)) % 100;
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
