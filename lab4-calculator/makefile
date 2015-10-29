CC = gcc
CFLAGS = -g -Wall
COMPILE = $(CC) $(CFLAGS)

TARGET = calculator.out


all: $(TARGET)

$(TARGET): calculator.o postfix.o stack.o strutil.o tokenizer.o
	$(COMPILE) -o $(TARGET) calculator.o postfix.o stack.o strutil.o tokenizer.o

calculator.o: calculator.c postfix.h
	$(COMPILE) -c calculator.c

postfix.o: postfix.c postfix.h stack.h strutil.h tokenizer.h
	$(COMPILE) -c postfix.c

stack.o: stack.c stack.h
	$(COMPILE) -c stack.c

strutil.o: strutil.c strutil.h
	$(COMPILE) -c strutil.c

tokenizer.o:  tokenizer.c  tokenizer.h
	$(COMPILE) -c tokenizer.c	

clean:
	$(RM) $(TARGET) *.o
