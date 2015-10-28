#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "strutil.h"
#include "stack.h"
#include "postfix.h"

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
            double_stack_push(stack, value);
        }
        /* If token is an operator then apply it to top two items in stack */
        else if (valid_operation(stack, token)) {
            double b = double_stack_pop(stack);
            double a = double_stack_pop(stack);
            double result = operate(a, b, token[0]);
            double_stack_push(stack, result);
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
        result = double_stack_pop(stack);
    }
    else {
        result = NAN;
    }
    stack_free(stack);
    return result;
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

char *infix_to_postfix(char *expression)
{
    const char delims[] = "()+-*/";

    stack_type stack = stack_new();
    tokenizer toke = tokenizer_new(expression, 0, delims);

    char *prev_token = "";
    while(next_token(toke)[0] != '\0') {
        char *token = get_token(toke);
        if (token[0] == '-') {

        }

        prev_token = token;
    }

    return null;
}

//Test client
int main()
{

    return 0;
}