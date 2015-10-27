CC = gcc
CFLAGS = -g -Wall
COMPILE = $(CC) $(CFLAGS)

TARGET = calculator.out


all: $(TARGET)

$(TARGET): postfix.o stack.o strutil.o
	$(COMPILE) -o $(TARGET) postfix.o stack.o strutil.o

postfix.o: postfix.c postfix.h stack.h strutil.h
	$(COMPILE) -c postfix.c

stack.o: stack.c stack.h
	$(COMPILE) -c stack.c

strutil.o: strutil.c strutil.h
	$(COMPILE) -c strutil.c

clean:
	$(RM) $(TARGET) *.o
