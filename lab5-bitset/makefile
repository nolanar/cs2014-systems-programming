CC = gcc
CFLAGS = -g -Wall -std=c99
COMPILE = $(CC) $(CFLAGS)


all: lab5.out

lab5.out: lab5.o bitset.o
	$(COMPILE) -o lab5.out lab5.o bitset.o

lab5.o: lab5.c bitset.h
	$(COMPILE) -c lab5.c

bitset.o: bitset.c bitset.h
	$(COMPILE) -c bitset.c

clean:
	$(RM) *.out *.o
