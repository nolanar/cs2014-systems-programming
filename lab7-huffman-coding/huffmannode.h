#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

/**
 * Node to be used in a huffman tree.
 */
typedef struct node *huff_node;

/**
 * Constructs a new leaf node.
 */
huff_node new_leaf_node(unsigned char ch, int weight);

/**
 * Constructs a new parent node.
 */
huff_node new_parent_node(huff_node left, huff_node right);

/**
 * Destroyes a node.
 *
 * NOTE: 
 * Any nodes that are children of this node are NOT destroyed.
 */
void free_node(huff_node this);

/**
 * Returns:
 * 0 if this is a leaf node
 * 1 if this is a parent node
 */
int is_leaf(huff_node this);

/**
 * Gets the weight of the specified node.
 */
int get_weight(huff_node this);

/**
 * Gets the char value from a leaf node.
 *
 * assert: must be a leaf node
 */
unsigned char get_char(huff_node this);

/**
 * Gets the left child of a parent node.
 *
 * assert: must be a parent node
 */
huff_node left_child(huff_node this);

/**
 * Gets the right child of a parent node.
 *
 * assert: must be a parent node
 */
huff_node right_child(huff_node this);

/**
 * Sorts an array of nodes in ascending order.
 *
 * The sorts algorithm used is an in-place quicksort.
 */
void sort_nodes(huff_node *nodes, int length);

/**
 * Searches a sorted array of nodes.
 *
 * Performes a binary search comparing node weight.
 */
int binary_search_nodes(huff_node *nodes, int length, huff_node node);

#endif