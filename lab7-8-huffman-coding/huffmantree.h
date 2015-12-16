#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

/* number of possible elements plus 1 for terminating character */
#ifndef TABLE_SIZE
#define TABLE_SIZE  257
#endif

/**
 * Huffman tree of chars.
 */
typedef struct tree *huff_tree;

/**
 * Constructs a new Huffman tree.
 */
huff_tree new_tree(int *char_freq);

/**
 * Destroy this Huffman tree.
 */
void free_tree(huff_tree);

/**
 * Gets the coding corresponding to specified key.
 *
 * assert: key must be valid
 */
char *get_coding(huff_tree this, unsigned key);

#endif