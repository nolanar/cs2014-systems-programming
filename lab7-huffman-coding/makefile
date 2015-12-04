CC = clang
CFLAGS =
COMPILE = $(CC) $(CFLAGS)


all: lab7.out

lab7.out: reader.o huffmantree.o huffmannode.o
	$(COMPILE) -o lab7.out reader.o huffmantree.o huffmannode.o

reader.o: reader.c huffmantree.h
	$(COMPILE) -c reader.c

huffmantree.o: huffmantree.c huffmantree.h huffmannode.h
	$(COMPILE) -c huffmantree.c

huffmannode.o: huffmannode.c huffmannode.h
	$(COMPILE) -c huffmannode.c

clean:
	$(RM) *.out *.o
