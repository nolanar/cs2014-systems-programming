#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct node {
    double data;
    struct node *next;
} *node_t;

struct stack {
    node_t top;
    size_t size;
};

stack_t stack_new()
{
    stack_t stack = (stack_t) malloc(sizeof(struct stack));
    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void stack_free(stack_t stack)
{
    while (!stack_isempty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}

void stack_push(stack_t stack, double value)
{
    // Create new node
    node_t top_new = (node_t) malloc(sizeof(struct node));
    top_new->data = value;
    top_new->next = stack->top;

    // Point top to new node
    stack->top = top_new;
    stack->size++;
}

double stack_pop(stack_t stack)
{
    // Precondition: stack must not be empty
    assert(!stack_isempty(stack));

    // Get value of top element
    node_t top_old = stack->top;
    double value = top_old->data;

    // Point top to next in list
    stack->top = top_old->next;
    stack->size--;

    free(top_old);
    return value;
}

_Bool stack_isempty(stack_t stack)
{
    return stack->top == NULL;
}

size_t stack_size(stack_t stack)
{
    return stack->size;
}
