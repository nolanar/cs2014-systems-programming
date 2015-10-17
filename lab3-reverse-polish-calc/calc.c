#include <stdio.h>
#include <string.h>
#include "token.h"
#include "stack.h"

#define MAX_STRING 256

double evaluate(char *expression);
_Bool isoperator(char *token);

int main()
{
    char expression[MAX_STRING];
    do {
        printf(">>> ");
        fgets(expression, MAX_STRING, stdin);
        // End program if 'quit' is entered by user.
        if (strcmp(expression, "quit\n") == 0) {
            break;
        }
        double result = evaluate(expression);
        printf("Result: %g\n", result);
    } while (1);

    return 0;
}

double evaluate(char *expression)
{
    char token[MAX_STRING];
    stack_t stack = stack_new();
    int index = tokenise(expression, 0, token);
    while (index != -1) {
        double value;
        int isdouble = sscanf(token, "%lf", &value);
        if (isdouble) {
            stack_push(stack, value);
        } else if (isoperator(token)) {
            double a = stack_pop(stack);
            double b = stack_pop(stack);
            char ch = token[0];
            double result =
                ch == '+' ? a + b:
                ch == '-' ? a - b:
                ch == '*' ? a * b:
                ch == '/' ? a / b:
                0;
            stack_push(stack, result);
        }
        index = tokenise(expression, index, token);
    }
    double result = stack_pop(stack);
    stack_free(stack);
    return result;
}

_Bool isoperator(char *token)
{
    char ch = token[0];
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
