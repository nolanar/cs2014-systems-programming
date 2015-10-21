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

stack_type stack_new()
{
    stack_type stack = (stack_type) malloc(sizeof(struct stack));
    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void stack_free(stack_type stack)
{
    while (!stack_isempty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}

void stack_push(stack_type stack, double value)
{
    /* Create new node */
    struct node *top_new = malloc(sizeof(struct node));
    top_new->data = value;
    top_new->next = stack->top;

    /* Point top to new node */
    stack->top = top_new;
    stack->size++;
}

double stack_pop(stack_type stack)
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

_Bool stack_isempty(stack_type stack)
{
    return stack->top == NULL;
}

size_t stack_size(stack_type stack)
{
    return stack->size;
}
