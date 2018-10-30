OBJECTS		=main.o hash_functions.o help_functions.o index_functions.o result.o
SOURCE		=main.c hash_functions.c help_functions.c index_functions.c result.c
OUTPUT		=main
HEADER  	=relation.h hash_functions.h help_functions.h result.h
CC			=gcc
FLAGS   	= -g -c -Wall

main: $(OBJECTS)
	$(CC) -g $(OBJECTS) -o $@

main.o: main.c
	$(CC) $(FLAGS) main.c

hash_functions.o: hash_functions.c
	$(CC) $(FLAGS) hash_functions.c

help_functions.o: help_functions.c
	$(CC) $(FLAGS) help_functions.c

index_functions.o: index_functions.c
	$(CC) $(FLAGS) index_functions.c

result.o: result.c
	$(CC) $(FLAGS) result.c

clean:
	rm $(OUTPUT) $(OBJECTS)
