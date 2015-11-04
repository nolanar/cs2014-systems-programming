#include <stdio.h>
#include <string.h>
#include "bitset.h"

/**
 * Map string to char bitset.
 */
void string_into_bitset(char *str, bitset_type set);

/**
 * Print space separated list of chars representing char bitset.
 */
void print_chars_in_set(bitset_type set);

int main()
{
    int buffersize = 128;
    char buffer[buffersize];

    printf("Input line 1: ");
    fgets(buffer, buffersize, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove trailing newline char
    bitset_type set_a = bitset_new(256);
    string_into_bitset(buffer, set_a);
    

    printf("Input line 2: ");
    fgets(buffer, buffersize, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove trailing newline char
    bitset_type set_b = bitset_new(256);
    string_into_bitset(buffer, set_b);

    printf("\nset A = chars that appear in line 1:\n");
    print_chars_in_set(set_a);

    printf("\nset B = chars that appear in line 2:\n");
    print_chars_in_set(set_b);

    printf("\nUnion of set A and set B:\n");
    bitset_type set_union = bitset_union(set_a, set_b);
    print_chars_in_set(set_union);

    printf("\nIntersection of set A and set B:\n");
    bitset_type set_intersection = bitset_intersection(set_a, set_b);
    print_chars_in_set(set_intersection);

    bitset_free(set_a);
    bitset_free(set_b);
    bitset_free(set_union);
    bitset_free(set_intersection);

    return 0;
}

void string_into_bitset(char *str, bitset_type set)
{
    int i = 0;
    char ch = str[i];
    while (ch != '\0') {
        bitset_add(set, (int) ch);
        ch = str[++i];
    }
}

void print_chars_in_set(bitset_type set)
{
    int thing = 1;
    for (int i = 0; i < bitset_size(set); i++) {
        if (bitset_lookup(set, i) == thing) {
            printf("%c ", i);
        }
    }
    printf("\n");
}