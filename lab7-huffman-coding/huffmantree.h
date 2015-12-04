#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

/**
 * Huffman tree of chars.
 */
typedef struct tree *huff_tree;

/**
 * Constructs a new Huffman tree.
 */
huff_tree new_tree(int *char_freq);

/**
 * Prints the Huffman coding represented by the tree.
 */
void print_tree(huff_tree this);

#endif