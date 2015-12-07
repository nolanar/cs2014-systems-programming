#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffmantree.h"

void print_table(int *table)
{
    for (int i = 0; i < 256; i++) {
        printf("%d%c", table[i], ((i+1)%8  == 0 ? '\n' : '\t'));
    }
}

/**
 * Change any 0 elemenets to 1.
 */
void zero_to_one(int *table)
{
    for (int i = 0; i < 256; i++) {
        if (table[i] == 0) {
            table[i] = 1;
        }
    }
}

int main(int argc, char ** argv)
{
    /* frequency vector */
    int char_freq[256];
    for (int i = 0; i < 256; i++) {
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

    zero_to_one(char_freq);
    print_table(char_freq);
    
    huff_tree tree = new_tree(char_freq);
    print_tree(tree);

    return 0;  // exit without error code
}