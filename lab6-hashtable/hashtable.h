#ifndef HASHTABLE
#define HASHTABLE

/**
 * Hashtable of strings.
 */
typedef struct hashtable *hashtable;

/**
 * Constructor.
 */
struct hashtable *hashtable_new(int size);

/**
 * Destructor.
 */
void hashtable_free(struct hashtable *this);

/**
 * Insert string into the hash table.
 *
 * No effect if it is already there.
 */
void hashtable_insert(struct hashtable *this, char *str);

/**
 * Remove string from the hash table.
 *
 * No effect if not in table.
 */
void hashtable_remove(struct hashtable *this, char *str);

/**
 * Returns whether the specified string is contained in the hashtable.
 *
 * Returns:
 * 0 if str is not in the hashtable
 * 1 if str is in the hashtable
 */
int hashtable_lookup(struct hashtable *this, char *str);

/**
 * Prints the srtings containted in each entry of the hashtable.
 */
void hashtable_print(struct hashtable *this);

#endif