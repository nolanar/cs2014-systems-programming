#ifndef BITSET
#define BITSET

typedef struct bitset *bitset_type;

bitset_type bitset_new(int size);

void bitset_free(bitset_type this);

int bitset_add(bitset_type this, int item);

int bitset_remove(bitset_type this, int item);

int bitset_lookup(bitset_type this, int item);

int bitset_size(bitset_type this);

bitset_type bitset_union(bitset_type setA, bitset_type setB);

bitset_type bitset_intersection(bitset_type setA, bitset_type setB);

#endif