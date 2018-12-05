OBJECTS		=main.o hash_functions.o help_functions.o index_functions.o result.o relation.o
OBJECTS2    =unit_testing.o hash_functions.o help_functions.o index_functions.o result.o relation.o
SOURCE		=main.c hash_functions.c help_functions.c index_functions.c result.c relation.c
OUTPUT		=main
OUTPUT2		=utest
HEADER  	=relation.h hash_functions.h help_functions.h result.h parsing_unit.h
HEADER2  	=unit_testing.h help_functions.h
CC			=gcc-8
FLAGS   	= -g -c -Wall
FLAGS2   	= -g -c -Wall -I$HOME/local/include

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

relation.o: relation.c
	$(CC) $(FLAGS) relation.c

utest: $(OBJECTS2)
	$(CC) -g $(OBJECTS2) -o $@ -lcunit


clean:
	rm $(OUTPUT) $(OBJECTS)

clean_unit_test:
	rm $(OUTPUT2) $(OBJECTS2)
