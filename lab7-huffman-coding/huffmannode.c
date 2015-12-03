#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "huffmannode.h"

#define swap(x, y) \
{ \
    struct node *swap = (x); \
    (x) = (y); \
    (y) = swap; \
}

/**
 * Compares the weight of two nodes.
 *
 * Returns the difference of their weight:
 * return < 0 if this < that
 * return = 0 if this == that
 * return > 0 if this > that
 */
int compare(struct node *this, struct node *that);

struct node {
    int weight;
    int is_leaf;
    union {
        struct {
            struct node *left;
            struct node *right;
        } children;
        unsigned char ch;
    } value;
};

struct node *new_leaf_node(unsigned char ch, int weight)
{
    struct node *this = malloc(sizeof *this);
    this->weight = weight;
    this->value.ch = ch;
    this->is_leaf = 1;
    return this;
}

struct node *new_parent_node(struct node *left, struct node *right)
{
    struct node *this = malloc(sizeof *this);
    this->weight = left->weight + right->weight;
    this->value.children.left = left;
    this->value.children.right = right;
    this->is_leaf = 0;
    return this;
}

void free_node(struct node *this)
{
    free(this);
}

int is_leaf(struct node *this)
{
    return this->is_leaf;
}

int get_weight(struct node *this)
{
    return this->weight;
}

int compare(struct node *this, struct node *that) 
{
    return this->weight - that->weight;
}

/**
 * In-place quicksort of an array of nodes.
 */
void sort_nodes(struct node **nodes, int length)
{
    if (length < 2) {
        return;
    }
    if (length == 2) {
        /* swap if the only two nodes are in the wrong order */
        if (compare(nodes[0], nodes[1]) > 0) {
            swap(nodes[0], nodes[1]);
        }
        return;
    }
    /* use middle node as pivot */
    swap(nodes[length / 2], nodes[length - 1]);
    struct node *pivot = nodes[length - 1];
    /* find left and right nodes in wrong order */
    int left = 0;
    int right = length - 2;
    while (left <= right) {
        /* find rightmost node in wrong order to pivot */
        while(left <= right && compare(pivot, nodes[right]) <= 0) {
            right--;
        }
        /* find leftmost node in wrong order to pivot*/
        while (left <= right && compare(nodes[left], pivot) <= 0) {
            left++;
        }
        /* swap left and right if were found out of order */
        if (left <= right) {
            if (left != right) {
                swap(nodes[left], nodes[right]);
            }
            left++;
            right--;
        }
    }
    /* swap pivot and node at which left and right crossed */
    int swap_pos = right + 1;
    if (swap_pos != length - 1) {
        swap(nodes[swap_pos], nodes[length - 1])
    }
    /* call sort on left and right subarrays */
    sort_nodes(nodes, swap_pos);
    sort_nodes(nodes + (swap_pos + 1), length - (swap_pos + 1));
}

/**
 * test client
 */
int main()
{
    struct node *parent = new_parent_node(new_leaf_node('l', 5), new_leaf_node('r', 10));
    struct node *left = parent->value.children.left;
    struct node *right = parent->value.children.right;
    printf("parent: %d, %d\n  left: %c, %d\n  right: %c, %d\n", 
        parent->is_leaf, parent->weight,
        left->value.ch, left->weight,
        right->value.ch, right->weight
        );

    int size = 26;
    struct node *nodes[size];
    for (int i = 0; i < size; i++) {
        nodes[i] = new_leaf_node('a' + i, rand() % 100);
    }
    printf("\npre-sort:\n");
    for (int i = 0; i < size; i++) {
        printf("%c: %d\n", nodes[i]->value.ch, nodes[i]->weight);
    }

    sort_nodes(nodes, size);
    printf("\npost-sort:\n");
    for (int i = 0; i < size; i++) {
        printf("%c: %d\n", nodes[i]->value.ch, nodes[i]->weight);
    }

}