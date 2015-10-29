#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "strutil.h"
#include "stack.h"
#include "tokenizer.h"
#include "postfix.h"

int priv_higher_prec(char op_1, char op_2);

double evaluate(char *expression)
{
    stack_type stack = stack_new();
    tokenizer toke = tokenizer_new(expression, 0, "");
    _Bool expression_valid = 1;

    while (next_token(toke)[0] != '\0') {
        char *token = get_token(toke);
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
    }

    double result;
    /* There should be exactaly one number remaining on stack */
    if (expression_valid && stack_size(stack) == 1) {
        result = double_stack_pop(stack);
    }
    else {
        result = NAN;
    }
    tokenizer_free(toke);
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
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
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

char *infix_to_postfix(char *expression, char *result)
{
    const int max_size = (sizeof expression)/(sizeof expression[0]);
    char delims[] = "()+-*/";

    int index = 0;
    stack_type stack = stack_new();
    tokenizer toke = tokenizer_new(expression, 0, delims);

    char prev_token[max_size];
    prev_token[0] = '\0';
    char temp_token[max_size];
    while(next_token(toke)[0] != '\0') {
        char *token = get_token(toke);
        // concatenate if two consecutive tokens correspond to a negative value
        if (!is_double(prev_token) && token[0] == '-' &&
                is_double(peek_token(toke, temp_token))) {
            next_token(toke);
            token[0] = '-';
            strcpy(token + 1, temp_token);
        }

        if (is_double(token)) {
            int i = 0;
            char ch = token[i];
            while(ch != '\0') {
                result[index++] = ch;
                ch = token[++i];
            }
            result[index++] = ' ';
        } 
        else if (token[0] == '(') {
            char_stack_push(stack, '(');
        }
        else if (is_operator(token[0])) {
            while (!stack_isempty(stack) &&
                    priv_higher_prec(char_stack_peek(stack), token[0])) {
                result[index++] = char_stack_pop(stack);
                result[index++] = ' ';
            } 
            char_stack_push(stack, token[0]);
        }
        else if (token[0] == ')') {
            char op = char_stack_pop(stack);
            while (op != '(') {
                result[index++] = op;
                result[index++] = ' ';
                op = char_stack_pop(stack);
            }
        }
        strcpy(prev_token, token);
    }

    while (!stack_isempty(stack)) {
        result[index++] = char_stack_pop(stack);
        result[index++] = ' ';
    }

    result[index] = '\0';
    stack_free(stack);
    tokenizer_free(toke);
    return result;
}

int priv_higher_prec(char op_1, char op_2)
{
    const char order[] = "/*-+";

    int i = 0;
    char op = order[i];
    while (op != '\0') {
        if (op_2 == op) {
            return 0;
        } else if (op_1 == op) {
            return 1;
        }
        op = order[++i];
    }
    return 0;
}
