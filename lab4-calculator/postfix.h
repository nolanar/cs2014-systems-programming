#ifndef CALC_H
#define CALC_H

#include "stack.h"

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

/** Converts a string in infix notation to postfix notation.
 *
 *  Parameters:
 *  char expression[] = infix expression
 *  char result[] = equivalent postfix expression
 *  
 *  note: 
 *  result should be big enough to fit expression expanded
 *  with spaces. Double the size of expression necessarily
 *  satisfies this condition.
 *
 *  note: 
 *  Does not check if string is valid infix expression.
 */
char *infix_to_postfix(char *expression, char *result);

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
