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

/** Returns:
<<<<<<< HEAD
 *  a `op` b    if op is in {'+', '-', '*', '/'}
=======
 *  b `op` a    if op is in {'+', '-', '*', '/'}
>>>>>>> refs/remotes/origin/master
 *  NAN         otherwise
 */
double operate(double a, double b, char op);

int main()
{
    printf(HELP_TEXT);
    char expression[MAX_STRING];
    do {
        printf(">>> ");
        fgets(expression, MAX_STRING, stdin);
        /* End program if user enters 'quit' */
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

enum evaluate_state {WELL_FORMED, MALFORMED, ZERO_DIVISION};

double evaluate(char *expression)
{
    stack_type stack = stack_new();
    enum evaluate_state state = WELL_FORMED;

    char token[MAX_STRING];
    int index = tokenise(expression, 0, token);
    while (index != -1) {
        double value;
        char invalid = '\0';
        int isdouble = sscanf(token, "%lf %c", &value, &invalid);
        if (isdouble && !invalid) {
            stack_push(stack, value);
        } else if (isoperator(token) && stack_size(stack) > 1) {
            double b = stack_pop(stack);
            double a = stack_pop(stack);
            double result = operate(a, b, token[0]);
            if (!isfinite(result)) {
                state = ZERO_DIVISION;
                break;
            }
            stack_push(stack, result);
        } else {
            state = MALFORMED;
            break;
        }
        index = tokenise(expression, index, token);
    }

    double result;
    if (state == WELL_FORMED && stack_size(stack) == 1) {
        result = stack_pop(stack);
    } else if (state == ZERO_DIVISION) {
        result = INFINITY;
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

double operate(double a, double b, char op)
{
<<<<<<< HEAD
    return op == '+' ? a + b:
           op == '-' ? a - b:
           op == '*' ? a * b:
           op == '/' ? a / b:
=======
    return op == '+' ? b + a:
           op == '-' ? b - a:
           op == '*' ? b * a:
           op == '/' ? b / a:
>>>>>>> refs/remotes/origin/master
           NAN;
}
