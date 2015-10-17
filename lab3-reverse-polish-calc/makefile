CC = gcc
CFLAGS = -g -Wall
COMPILE = $(CC) $(CFLAGS)

TARGET = a.out

all: $(TARGET)

$(TARGET): calc.o stack.o token.o
	$(COMPILE) -o $(TARGET) calc.o stack.o token.o

calc.o: calc.c stack.h token.h
	$(COMPILE) -c calc.c

stack.o: stack.c stack.h
	$(COMPILE) -c stack.c

token.o: token.c token.h
	$(COMPILE) -c token.c

clean:
	$(RM) $(TARGET) *.o
