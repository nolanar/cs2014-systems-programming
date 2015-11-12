#ifndef HASHTABLE
#define HASHTABLE

typedef struct hashtable *hashtable;

struct hashtable *hashtable_new(int size);

void hashtable_free(struct hashtable *this);

void hashtable_insert(struct hashtable *this, char *str);

void hashtable_remove(struct hashtable *this, char *str);

int hashtable_lookup(struct hashtable *this, char *str);

void hashtable_print(struct hashtable *this);

#endif