#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "huffmannode.h"

//-->DEBUG
void printn(huff_node node){
    printf("%c: %d\n", get_char(node), get_weight(node));
}
void printw(huff_node node){
    printf("    : %d\n", get_weight(node));
}
//--<

void join_smallest(huff_node *nodes, int length);
void print_node(huff_node root, int path, int depth);

struct tree {
    huff_node root;
};

struct tree *new_tree(int *char_freq)
{
    struct tree *this = malloc(sizeof *this);
    /* create an array containing the leaves of the tree */
    huff_node nodes[256];
    for (int i = 0; i < 256; i++) {
        nodes[i] = new_leaf_node(i, char_freq[i]);
    }
    /* Sort the array in ascending order */
    sort_nodes(nodes, 256);
    /* repeatedly join two smallest nodes until just one remains */
    for (int i = 0; i < 255; i++) {
        join_smallest(nodes, 256 - i);
    }
    this->root = nodes[0];
    return this;
}

void print_tree(struct tree *this)
{
    print_node(this->root, 0, 0);
}

void print_node(huff_node root, int path, int depth)
{
    if (is_leaf(root)) {
        printf("%c: ", get_char(root));
        for (int i = 0; i < depth; i++) {
            printf("%d", path >> i & 1);
        }
        printf("\n");
        return;
    }
    print_node(left_child(root), path, depth + 1);
    print_node(right_child(root), path | 1 << depth, depth + 1);
}

/**
 * Join two smallest nodes and maintain ordering.
 *
 * The given node array is assumed to be in ascending order.
 */
void join_smallest(huff_node *nodes, int length)
{
    huff_node joined = new_parent_node(nodes[0], nodes[1]);
    /* Insert 'joined' into 'nodes' in correct position */
    int index = binary_search_nodes(nodes + 2, length - 2, joined);
    memmove(nodes, nodes + 2, index * sizeof(huff_node));
    int size = (length - 2 - index) * sizeof(huff_node);
    memmove(nodes + index + 1, nodes + 2 + index, size);
    nodes[index] = joined;
    nodes[length - 1] = NULL;
}