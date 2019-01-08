OBJECTS		=main.o hash_functions.o help_functions.o index_functions.o result.o relation.o queue.o parsing_unit.o job_scheduler.o queue3.o
OBJECTS2    =unit_testing.o hash_functions.o help_functions.o index_functions.o result.o relation.o queue.o
SOURCE		=main.c hash_functions.c help_functions.c index_functions.c result.c relation.c queue.c parsing_unit.c job_scheduler.c queue3.c
OUTPUT		=main
OUTPUT2		=utest
HEADER  	=relation.h hash_functions.h help_functions.h result.h parsing_unit.h job_scheduler.h queue3.h
HEADER2  	=unit_testing.h help_functions.h
CC			=gcc
FLAGS   	= -g -c -Wall -O3
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

queue.o: queue.c
	$(CC) $(FLAGS) queue.c

queue3.o: queue3.c
	$(CC) $(FLAGS) queue3.c

parsing_unit.o: parsing_unit.c
	$(CC) $(FLAGS) parsing_unit.c

job_scheduler.0: job_scheduler.c
	$(CC) $(FLAGS) job_scheduler.c

utest: $(OBJECTS2)
	$(CC) -g $(OBJECTS2) -o $@ -lcunit


clean:
	rm $(OUTPUT) $(OBJECTS)

clean_unit_test:
	rm $(OUTPUT2) $(OBJECTS2)
