#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

/**
 * Node to be used in a huffman tree.
 */
typedef struct node *huff_node;

/**
 * Constructs a new leaf node.
 */
struct node *new_leaf_node(unsigned char ch, int weight);

/**
 * Constructs a new parent node.
 */
struct node *new_parent_node(struct node *left, struct node *right);

/**
 * Destroyes a node.
 *
 * NOTE: 
 * Any nodes that are children of this node are NOT destroyed.
 */
void free_node(struct node *this);

/**
 * Returns:
 * 0 if this is a leaf node
 * 1 if this is a parent node
 */
int is_leaf(struct node *this);

/**
 * Gets the weight of the specified node.
 */
int get_weight(struct node *this);

/**
 * Sorts an array of nodes.
 *
 * The sorts algorithm used is an in-place quicksort.
 */
void sort_nodes(struct node **nodes, int length);

#endif