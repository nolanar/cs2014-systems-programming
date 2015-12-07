#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include "huffmannode.h"

struct tree {
    huff_node root;
    char **coding_table;
};

void priv_join_smallest(huff_node *nodes, int length);
void priv_print_node(huff_node root, int path, int depth);
void priv_code_leaves(struct tree *this, huff_node root, char *path, int depth);

struct tree *new_tree(int *char_freq, int size)
{
    struct tree *this = malloc(sizeof *this);
    this->coding_table = malloc(256 * (sizeof *this->coding_table));
    /* create an array containing the leaves of the tree */
    huff_node nodes[256];
    for (int i = 0; i < 256; i++) {
        nodes[i] = new_leaf_node(i, char_freq[i]);
    }
    /* Sort the node array in ascending order */
    sort_nodes(nodes, 256);
    /* repeatedly join two smallest nodes until just one remains */
    for (int i = 0; i < 255; i++) {
        priv_join_smallest(nodes, 256 - i);
    }
    /* let this be the root of the huffman tree */
    this->root = nodes[0];
    /* embed the path to each leaf into the leaves */
    priv_code_leaves(this, this->root, NULL, 0);
    return this;
}

void free_tree(struct tree *this)
{
    // TODO: implement
}

char *get_coding(struct tree *this, unsigned key)
{
    return this->coding_table[key];
}

void priv_code_leaves(struct tree *this, huff_node root, char *path, int depth)
{
    
    if (is_leaf(root)) {
        /* create null terminated string from current path */
        char *coding = malloc(depth + 1);
        memcpy(coding, path, depth);
        coding[depth] = '\0';
        /* set the coding corresponding to the leaf nodes as the path string */
        this->coding_table[get_char(root)] = coding;
        return;
    }
    /* if a parent node, recursively traverse children */
    /* left child traverse */
    char left_path[depth + 1];
    memcpy(left_path, path, depth);
    left_path[depth] = '0';
    priv_code_leaves(this, left_child(root), left_path, depth + 1);
    /* right child traverse */
    char right_path[depth + 1];
    memcpy(right_path, path, depth);
    right_path[depth] = '1';
    priv_code_leaves(this, right_child(root), right_path, depth + 1);
}

void print_tree(struct tree *this)
{
    for (int i = 0; i < 256; i++) {
        printf("%c:\t%s\n", i, this->coding_table[i]);
    }
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