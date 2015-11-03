#include <stdlib.h>
#include <limits.h>
#include "bitset.h"

struct bitset {
    int size;
    unsigned char *bitvector;
};

int priv_in_range(struct bitset *this, int index);
int priv_get_row(struct bitset *this, int index);
void priv_set_row(struct bitset *this, int index, unsigned char row);
int priv_get_bit(struct bitset *this, int index);

struct bitset *bitset_new(int size)
{
    struct bitset *this = malloc(sizeof *this);
    this->size = size;
    int char_count = size / CHAR_BIT + !!(size % CHAR_BIT); // add 1 if remainder
    this->bitvector = calloc(char_count, 1); // char defined as 1 unit of memroy
    return this;
}

void bitset_free(struct bitset *this)
{
    free(this->bitvector);
    free(this);
}

int bitset_add(struct bitset *this, int item)
{
    int result = priv_in_range(this, item);
    if (result) {
        unsigned char row = priv_get_row(this, item);
        int index_in_row = item % CHAR_BIT;
        row = row | (1 << index_in_row);
        priv_set_row(this, item, row);
    }
    return result;
}

int bitset_remove(struct bitset *this, int item)
{
    int result = priv_in_range(this, item);
    if (result) {
        unsigned char row = priv_get_row(this, item);
        int index_in_row = item % CHAR_BIT;
        row = row & ~(1 << index_in_row);
        priv_set_row(this, item, row);
    }
    return result;
}

int bitset_lookup(struct bitset *this, int item)
{
    int result;
    if (priv_in_range(this, item)) {
        result = priv_get_bit(this, item);
    } else {
        result = -1;
    }
    return result;
}

int bitset_size(struct bitset *this)
{
    return this->size;
}

struct bitset *bitset_union(struct bitset *set_a, struct bitset *set_b)
{
    struct bitset *result;
    int size_a = bitset_size(set_a);
    int size_b = bitset_size(set_b);
    if (size_a == size_b) {
        result = bitset_new(size_a);
        for (int i = 0; i < size_a; i += CHAR_BIT) {
            unsigned char rowA = priv_get_row(set_a, i);
            unsigned char rowB = priv_get_row(set_b, i);
            unsigned char row = rowA | rowB;
            priv_set_row(result, i, row);
        }
    }
    else {
        result = NULL;
    }
    return result;
}

struct bitset *bitset_intersection(struct bitset *set_a, struct bitset *set_b)
{
    struct bitset *result;
    int size_a = bitset_size(set_a);
    int size_b = bitset_size(set_b);
    if (size_a == size_b) {
        result = bitset_new(size_a);
        for (int i = 0; i < size_a; i += CHAR_BIT) {
            unsigned char rowA = priv_get_row(set_a, i);
            unsigned char rowB = priv_get_row(set_b, i);
            unsigned char row = rowA & rowB;
            priv_set_row(result, i, row);
        }
    }
    else {
        result = NULL;
    }
    return result;
}

/**
 * Private functions:
 */

int priv_in_range(struct bitset *this, int index)
{
    return 0 <= index && index < this->size;
}

int priv_get_row(struct bitset *this, int index)
{
    return this->bitvector[index / CHAR_BIT];
}

void priv_set_row(struct bitset *this, int index, unsigned char row)
{
    this->bitvector[index / CHAR_BIT] = row;
}

int priv_get_bit(struct bitset *this, int index)
{
    unsigned char bits = this->bitvector[index / CHAR_BIT];
    int bit = bits >> index % CHAR_BIT & 1;
    return bit;
}
