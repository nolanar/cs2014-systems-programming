#include <stdlib.h>
#include <stdio.h>
#include "strlist.h"

struct hashtable {
    int size;
    str_list *table;
};

struct hashtable *hashtable_new(int size)
{
    struct hashtable *this = malloc(sizeof *this);
    this->size = size;
    this->table = malloc(size * (sizeof *this->table));
    for (int i = 0; i < size; i++) {
        this->table[i] = list_new();
    }
    return this;
}

void hashtable_free(struct hashtable *this)
{
    for (int i = 0; i < this->size; i++) {
        list_free(this->table[i]);
    }
    free(this);
}

/**
 * Test client
 */
int main()
{
    struct hashtable *h;
}