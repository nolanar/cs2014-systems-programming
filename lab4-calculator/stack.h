#ifndef STACK_H
#define STACK_H

#include <stddef.h>

/** Stack data structure.
 *
 *  Node values are of type double.
 */
typedef struct stack *stack_type;

/** Returns a new empty stack.
 *
 *  note: This should be used when a new stack is required.
 */
stack_type stack_new();

/** Destroys stack.
 */
void stack_free(stack_type stack);

/** Puts new double valued element on top of stack.
 */
void stack_push(stack_type stack, double value);

/** Removes top element from stack and returns it's value.
 *
 *  Precondition:
 *  The stack must not be empty.
 */
double stack_pop(stack_type stack);

/** Returns: true if stack is empty, false otherwise.
 */
_Bool stack_isempty(stack_type stack);

/** Returns the number of elements on the stack.
 */
size_t stack_size(stack_type stack);

#endif
