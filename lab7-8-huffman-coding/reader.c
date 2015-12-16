#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffmantree.h"

/**
 * Note:
 * TABLE_SIZE defined in huffmantree.h
 */

int main(int argc, char ** argv)
{
    /* frequency vector */
    int char_freq[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        char_freq[i] = 0;
    }

    unsigned char c;
    FILE * file;

    if ( argc != 2 ) {
        fprintf(stderr, "Useage: huffman <filename>\n");
        exit(1);        // exit with error code
    }

    file = fopen(argv[1], "r");
    assert( file != NULL );
    c = fgetc(file);  // attempt to read a byte
    while( !feof(file) ) {
        // printf("%c", c);
        char_freq[c] += 1;
        c = fgetc(file);
    }
    fclose(file);

    char_freq[TABLE_SIZE - 1] = 1;
    
    huff_tree tree = new_tree(char_freq);
    free_tree(tree);

    return 0;  // exit without error code
}