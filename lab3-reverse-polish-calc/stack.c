#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

typedef struct node {
    int data;
    struct node *next;
} *node_t;

struct stack {
    node_t top;
};

stack_t stack_new() {
    stack_t stack = (stack_t) malloc(sizeof(struct stack));
    stack -> top = NULL;
    return stack;
}

void stack_free(stack_t stack) {
    assert(stack -> top == NULL);   /*! Precondition: stack must be empty. */
    free(stack);
}

void stack_push(stack_t stack, int value) {
    node_t new_top = (node_t) malloc(sizeof(struct node));
    new_top -> data = value;
    new_top -> next = stack -> top;
    stack -> top = new_top;
}

int stack_pop(stack_t stack) {
    assert(stack -> top != NULL);   /*! Precondition: stack must not be empty */
    node_t top_old = stack -> top;
    int value = top_old -> data;
    node_t top_new = top_old -> next;
    stack -> top = top_new;
    free(top_old);
    return value;
}
