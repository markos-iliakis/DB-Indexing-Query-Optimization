OBJECTS		=main.o
SOURCE		=main.c
OUTPUT		=main
HEADER  	=relation.h
CC			=gcc
FLAGS   	= -g -c -Wall

main: $(OBJECTS)
	$(CC) -g $(OBJECTS) -o $@

main.o: main.c
	$(CC) $(FLAGS) main.c
