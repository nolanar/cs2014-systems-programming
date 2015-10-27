#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct node {
    double data;
    struct node *next;
};

struct stack {
    struct node *top;
    size_t size;
};

struct stack *stack_new()
{
    struct stack *stack = malloc(sizeof *stack);
    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void stack_free(struct stack *stack)
{
    while (!stack_isempty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}

void stack_push(struct stack *stack, double value)
{
    /* Create new node */
    struct node *top_new = malloc(sizeof *top_new);
    top_new->data = value;
    top_new->next = stack->top;

    /* Point top to new node */
    stack->top = top_new;
    stack->size++;
}

double stack_pop(struct stack *stack)
{
    /* Precondition: stack must not be empty */
    assert(!stack_isempty(stack));

    /* Get value of top element */
    struct node *top_old = stack->top;
    double value = top_old->data;

    /* Point top to next in list */
    stack->top = top_old->next;
    stack->size--;

    free(top_old);
    return value;
}

_Bool stack_isempty(struct stack *stack)
{
    return stack->top == NULL;
}

size_t stack_size(struct stack *stack)
{
    return stack->size;
}
