#include <stdlib.h>
#include <stdio.h>
#include "strlist.h"

struct hashtable {
    int size;
    str_list *table;
};

/* Private functions */
unsigned priv_hash_string(char *str);
str_list priv_get_list(struct hashtable *this, char *str);

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

void hashtable_insert(struct hashtable *this, char *str)
{
    str_list list = priv_get_list(this, str);
    if (!list_lookup(list, str)) {
        list_add(list, 0, str);
    }
}

void hashtable_remove(struct hashtable *this, char *str)
{
    str_list list = priv_get_list(this, str);
    list_remove_item(list, str);
}

int hashtable_lookup(struct hashtable *this, char *str)
{
    str_list list = priv_get_list(this, str);
    return list_lookup(list, str);
}

void hashtable_print(struct hashtable *this)
{
    for (int i = 0; i < this->size; i++) {
        str_list list = this->table[i];
        printf("%d:", i);
        for (int j = 0; j < list_size(list); j++) {
            printf("\t%s\n", list_get(list, j));
        }
        if (list_size(list) == 0) {
            printf("\t<empty>\n");
        }
    }
}

/**
 * Private functions
 */
unsigned priv_hash_string(char *str)
{
  unsigned hash = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    hash = hash * 37 + str[i];
  }
  return hash;
}

str_list priv_get_list(struct hashtable *this, char *str)
{
    int index = priv_hash_string(str) % this->size;
    return this->table[index];    
}