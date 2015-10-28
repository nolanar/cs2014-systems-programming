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

/** Puts new value element on top of stack.
 */
void double_stack_push(stack_type stack, double value);
void char_stack_push(stack_type stack, char value);

/** Removes top element from stack and returns it's value.
 *
 *  Precondition:
 *  The stack must not be empty.
 */
double double_stack_pop(struct stack *stack);
char char_stack_pop(stack_type stack);

/** Returns: true if stack is empty, false otherwise.
 */
_Bool stack_isempty(stack_type stack);

/** Returns the number of elements on the stack.
 */
size_t stack_size(stack_type stack);

#endif
