OBJECTS		=main.o hash_functions.o
SOURCE		=main.c hash_functions.c
OUTPUT		=main
HEADER  	=relation.h hash_functions.h
CC			=gcc
FLAGS   	= -g -c -Wall

main: $(OBJECTS)
	$(CC) -g $(OBJECTS) -o $@

main.o: main.c
	$(CC) $(FLAGS) main.c

hash_functions.o: hash_functions.c
	$(CC) $(FLAGS) hash_functions.c

clean:
	rm $(OUTPUT) $(OBJECTS)
