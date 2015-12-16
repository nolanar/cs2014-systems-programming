#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include "huffmannode.h"
#include "huffmantree.h"

struct tree {
    huff_node root;
};

void priv_join_smallest(huff_node *nodes, int length);
void priv_print_node(huff_node root, int path, int depth);
void priv_code_leaves(struct tree *this, huff_node root, int depth);

struct tree *new_tree(int *char_freq)
{
    struct tree *this = malloc(sizeof *this);
    /* create an array containing the leaves of the tree */
    huff_node nodes[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        nodes[i] = new_leaf_node(i, char_freq[i]);
    }
    /* Sort the node array in ascending order */
    sort_nodes(nodes, TABLE_SIZE);
    /* repeatedly join two smallest nodes until just one remains */
    for (int i = 0; i < TABLE_SIZE - 1; i++) {
        priv_join_smallest(nodes, TABLE_SIZE - i);
    }
    /* let this be the root of the huffman tree */
    this->root = nodes[0];
    /* embed the path to each leaf into the leaves */
    priv_code_leaves(this, this->root, 0);
    return this;
}

void free_tree(struct tree *this)
{
    // TODO: implement
}

void priv_code_leaves(struct tree *this, huff_node root, int depth)
{
    
    if (is_leaf(root)) {
        set_depth(root, depth);
        printf("%d: %d\n", get_key(root), depth); // DEBUG
        return;
    }
    /* if a parent node, recursively traverse children */
    /* left child traverse */
    priv_code_leaves(this, left_child(root), depth + 1);
    /* right child traverse */
    priv_code_leaves(this, right_child(root), depth + 1);
}

/**
 * Join two smallest nodes and maintain ordering.
 *
 * The given node array is assumed to be in ascending order.
 */
void priv_join_smallest(huff_node *nodes, int length)
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