#ifndef STACK_H
#define STACK_H

#include <stddef.h>


/** 
 * Stack data structure.
 */
typedef struct stack *stack_type;

#define DECLARE_STACK(TYPE, NAME)                           \
/**                                                         \
 * Puts new TYPE element on top of stack.                   \
 *                                                          \
 * Example use:                                             \
 * double_stack_push(my_stack, 3.14)                        \
 */                                                         \
void NAME##_stack_push(stack_type, TYPE value);             \
/**                                                         \
 * Removes top element from stack and returns it's value.   \
 *                                                          \
 * Precondition:                                            \
 * The stack must not be empty.                             \
 *                                                          \
 * Example use:                                             \
 * double pi_approx = double_stack_pop(my_stack)            \
 */                                                         \
TYPE NAME##_stack_pop(stack_type);                          \
/**                                                         \
 * Returns but does not remove top element from the stack.  \
 *                                                          \
 * Precondition:                                            \
 * The stack must not be empty.                             \
 *                                                          \
 * Example use:                                             \
 * double pi_approx = double_stack_peek(my_stack)           \
 */                                                         \
TYPE NAME##_stack_peek(stack_type);


/**
 * Stack types and associated names.
 */
DECLARE_STACK(double, double);
DECLARE_STACK(char, char);
DECLARE_STACK(unsigned char, uchar);
DECLARE_STACK(int, int);
DECLARE_STACK(unsigned int, uint);

/** 
 * Returns a new empty stack.
 *
 * note: This should be used when a new stack is required.
 */
stack_type stack_new();

/** 
 * Destroys stack.
 */
void stack_free(stack_type stack);


/** 
 * Returns: true if stack is empty, false otherwise.
 */
_Bool stack_isempty(stack_type stack);

/**
 * Returns the number of elements on the stack.
 */
size_t stack_size(stack_type stack);

#endif
