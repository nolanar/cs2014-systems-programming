CC = gcc
CFLAGS = -g -Wall
COMPILE = $(CC) $(CFLAGS)

TARGET = calculator.out


all: $(TARGET)

$(TARGET): calc.o stack.o strutil.o
	$(COMPILE) -o $(TARGET) calc.o stack.o strutil.o

calc.o: calc.c calc.h stack.h strutil.h
	$(COMPILE) -c calc.c

stack.o: stack.c stack.h
	$(COMPILE) -c stack.c

strutil.o: strutil.c strutil.h
	$(COMPILE) -c strutil.c

clean:
	$(RM) $(TARGET) *.o
