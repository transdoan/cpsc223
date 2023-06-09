CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

HookBook: hookbook.o libhookbook.o array_list.o pirate_list.o pirate.o
	${CC} ${CFLAGS} -o $@ $^ -lm

hookbook.o: hookbook.c libhookbook.c array_list.c pirate_list.c pirate.c
libhookbook.o: libhookbook.c libhookbook.h
array_list.o: array_list.c array_list.h
pirate_list.o: pirate_list.c pirate_list.h 
pirate.o: pirate.c pirate.h 

clean:
	rm -f *.o
	rm -f Hookbook