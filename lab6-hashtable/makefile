CC = clang
CFLAGS =
COMPILE = $(CC) $(CFLAGS)


all: hashtable.out

hashtable.out: hashtable.o strlist.o
	$(COMPILE) -o hashtable.out hashtable.o strlist.o

hashtable.o: hashtable.c strlist.h
	$(COMPILE) -c hashtable.c

strlist.o: strlist.c strlist.h
	$(COMPILE) -c strlist.c

clean:
	$(RM) *.out *.o
