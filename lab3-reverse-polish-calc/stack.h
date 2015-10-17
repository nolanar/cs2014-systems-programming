#ifndef STACK_H
#define STACK_H

/** Stack data structure.
 *
 *  Node values are of type double.
 */
typedef struct stack *stack_t;

/** Returns a new empty stack.
 *
 *  note: This should be used when a new stack is required.
 */
stack_t stack_new();

/** Destroy stack.
 *
 *  Precondition:
 *  The stack must be empty.
 */
void stack_free(stack_t stack);

/** Puts new double valued element on top of stack.
 */
void stack_push(stack_t stack, double value);

/** Removes top element from stack and returns it's value.
 *
 *  Precondition:
 *  The stack must not be empty.
 */
int stack_pop(stack_t stack);

#endif
