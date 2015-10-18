#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "token.h"
#include "stack.h"

#define MAX_STRING 256

const char HELP_TEXT[] =
    "Enter an expression in reverse polish notation to evaluate.\n"
    "Operators:\n"
    "  +  Add\n"
    "  -  Subtract\n"
    "  *  Multiply\n"
    "  /  Divide\n"
    "Enter 'quit' to exit program.\n";

/** Evaluates an expression in reverse polish notation
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
 *  true        if token matches a double
 *  false       otherwise
 */
_Bool is_double(char *token);

/** Returns double that matches token
 *
 *  Precondition: token must match a double
 */
double get_double(char *token);

/** Returns:
 * true         if ch is operator char
 * false        otherwise
 *
 *  Operators:
 *  +   -   *   /
 */
_Bool is_operator(char ch);

/** Returns:
 *  true        if token is an operator and stack has at least 2 numbers
 *  flase       otherwise
 */
_Bool valid_operation(stack_type stack, char *token);

/** Returns:
 *  INFINITY    if division by 0 occurs
 *  a `op` b    otherwise
 *
 * Precondition: op is a valid operator char
 */
double operate(double a, double b, char op);

int main()
{
    printf(HELP_TEXT);
    char expression[MAX_STRING];
    do {
        printf(">>> ");
        fgets(expression, MAX_STRING, stdin);
        /* Exit input loop if user enters 'quit' */
        if (strcmp(expression, "quit\n") == 0) {
            break;
        }

        double result = evaluate(expression);

        if (isnan(result)) {
            printf("ERROR: expression is not well formed\n");
        }
        else if (!isfinite(result)) {
            printf("ERROR: division by 0 occured\n");
        }
        else {
            printf("%g\n", result);
        }
    } while (1);

    return 0;
}

double evaluate(char *expression)
{
    stack_type stack = stack_new();
    _Bool expression_valid = 1;

    char token[MAX_STRING];
    int index = tokenise(expression, 0, token);
    while (index != -1) {
        /* If token is a number then push to stack */
        if (is_double(token)) {
            double value = get_double(token);
            stack_push(stack, value);
        }
        /* If token is an operator then apply it to top two items in stack */
        else if (valid_operation(stack, token)) {
            double b = stack_pop(stack);
            double a = stack_pop(stack);
            double result = operate(a, b, token[0]);
            stack_push(stack, result);
        }
        /* If token is invalid then exit loop */
        else {
            expression_valid = 0;
            break;
        }
        index = tokenise(expression, index, token);
    }

    double result;
    /* There should be exactaly one number remaining on stack */
    if (expression_valid && stack_size(stack) == 1) {
        result = stack_pop(stack);
    }
    else {
        result = NAN;
    }
    stack_free(stack);
    return result;
}

_Bool is_double(char *token)
{
    double value;
    char invalid = '\0';
    int hasdouble = sscanf(token, "%lf %c", &value, &invalid);
    return hasdouble && !invalid;
}

double get_double(char *token)
{
    assert(is_double(token));

    double value;
    sscanf(token, "%lf", &value);
    return value;
}

_Bool valid_operation(stack_type stack, char *token)
{
    char ch = token[0];
    _Bool has_length_one = token[1] == '\0';
    _Bool has_operands = stack_size(stack) >= 2;
    return is_operator(ch) && has_length_one && has_operands;
}

_Bool is_operator(char ch)
{
    return ch == '+' || ch == '-'|| ch == '*' || ch == '/';
}

double operate(double a, double b, char op)
{
    assert(is_operator(op));

    double result =
        op == '+' ? a + b :
        op == '-' ? a - b :
        op == '*' ? a * b :
        op == '/' ? a / b :
        NAN;

    if (!isfinite(result)) {
        result = INFINITY;
    }

    return result;
}
