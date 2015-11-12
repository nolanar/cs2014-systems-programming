CC = clang
CFLAGS =
COMPILE = $(CC) $(CFLAGS)


all: lab6.out

lab6.out: lab6.o hashtable.o strlist.o
	$(COMPILE) -o lab6.out lab6.o hashtable.o strlist.o

lab6.o: lab6.c hashtable.h
	$(COMPILE) -c lab6.c

hashtable.o: hashtable.c strlist.h
	$(COMPILE) -c hashtable.c

strlist.o: strlist.c strlist.h
	$(COMPILE) -c strlist.c

clean:
	$(RM) *.out *.o
