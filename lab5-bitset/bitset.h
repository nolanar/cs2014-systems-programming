#ifndef BITSET
#define BITSET

/**
 * Bit Vector Set ADT.
 */
typedef struct bitset *bitset_type;

/**
 * Construct a new bitset.
 */
bitset_type bitset_new(int size);

/**
 * Destroy specified bitset.
 */
void bitset_free(bitset_type this);

/**
 * Adds item to set.
 * 
 * Parameter:
 * this - the set to add to
 * item - key value corresponding to item
 *
 * Return:
 * 0 if item is out of bounds
 * 1 otherwise
 */
int bitset_add(bitset_type this, int item);

/**
 * Remove item from set.
 * 
 * Parameter:
 * this - the set to remove from
 * item - key value corresponding to item
 *
 * Return:
 * 0 if item is out of bounds
 * 1 otherwise
 */
int bitset_remove(bitset_type this, int item);

/**
 * Check if item is in set.
 * 
 * Parameter:
 * this - the set to search
 * item - key value corresponding to item
 *
 * Return:
 * -1 if item is out of bounds
 * 0 if item not in the set 
 * 1 if item is in the set
 */
int bitset_lookup(bitset_type this, int item);

/**
 * Return the size of the set.
 */
int bitset_size(bitset_type this);

/**
 * Union of set_a and set_b.
 *
 * Return:
 * NULL if sets are not the same size (see [1])
 * The union if seta are the same size
 * 
 * [1] Both bitsets are expected to represent the same set 
 * thus be of the same size.
 */
bitset_type bitset_union(bitset_type set_a, bitset_type set_b);

/**
 * Union of set_a and set_b.
 * 
 * Return:
 * NULL if sets are not the same size (see [1])
 * The union if seta are the same size
 * 
 * [1] Both bitsets are expected to represent the same set 
 * thus be of the same size.
 */
bitset_type bitset_intersection(bitset_type set_a, bitset_type set_b);

#endif