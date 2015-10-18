#include <stdio.h>
#include <string.h>
#include <math.h>
#include "token.h"
#include "stack.h"

#define MAX_STRING 256

const char HELP_TEXT[] =
    "Enter an expression in reverse polish notation to evaluate.\n"
    "Enter 'quit' to exit program.\n";

/** Evaluates an expression in reverse polish notation.
 *
 *  Parameters:
 *  char expression[] = expression to be evaluated
 *
 *  Return:
 *  result      if expression is well formed
 *  NAN         if expression is not well formed
 *  INFINITY    if division by 0 occures
 */
double evaluate(char *expression);

/** Returns:
 *  true        if token consists of one of {'+', '-', '*', '/'}
 *  flase       otherwise
 */
_Bool isoperator(char *token);

int main()
{
    printf(HELP_TEXT);
    char expression[MAX_STRING];
    do {
        printf(">>> ");
        fgets(expression, MAX_STRING, stdin);
        // End program if user enters 'quit'
        if (strcmp(expression, "quit\n") == 0) {
            break;
        }
        double result = evaluate(expression);

        if (isnan(result)) {
            printf("ERROR: expression is not well formed\n");
        } else if (!isfinite(result)) {
            printf("ERROR: division by 0 occured\n");
        } else {
            printf("%g\n", result);
        }
    } while (1);

    return 0;
}

double evaluate(char *expression)
{
    stack_t stack = stack_new();

    char token[MAX_STRING];
    int index = tokenise(expression, 0, token);
    while (index != -1) {
        double value;
        char invalid = '\0';
        int isdouble = sscanf(token, "%lf %c", &value, &invalid);
        if (isdouble && !invalid) {
            stack_push(stack, value);
        } else if (isoperator(token) && stack_size(stack) > 1) {
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
        } else {
            return NAN;
        }
        index = tokenise(expression, index, token);
    }

    double result;
    if (stack_size(stack) == 1) {
        result = stack_pop(stack);
    } else {
        result = NAN;
    }
    stack_free(stack);
    return result;
}

_Bool isoperator(char *token)
{
    char ch = token[0];
    _Bool isopchar = ch == '+' || ch == '-'|| ch == '*' || ch == '/';
    return token[1] == '\0' && isopchar;
}
