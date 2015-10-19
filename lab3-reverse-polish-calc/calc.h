#ifndef CALC_H
#define CALC_H

#include "stack.h"

#define MAX_STRING 256

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
 *  true        if token matches a finite double
 *  false       otherwise
 */
_Bool is_double(char *token);

/** Returns double that matches token
 *
 *  Precondition: token must match a finite double
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

#endif
