#ifndef STRLIST
#define STRLIST

#include <stddef.h>

/**
 * Linked list of strings.
 */
typedef struct list {
    int size;
    struct node *head;
    struct node *tail;
} *str_list;

/**
 * Constructor.
 */
str_list list_new();

/**
 * Destructor.
 */
void list_free(str_list this);

/**
 * Inserts the specified string at the specified position in this list. 
 * 
 * Shifts any proceeding elements up one index.
 *
 * Returns:
 * 0 if index out of range
 * 1 otherwise
 */
int list_add(str_list this, int index, char *str);

/**
 * Replaces the string at the specified position in the list.
 *
 * Returns:
 * 0 if index out of range
 * 1 otherwise
 */
int list_set(str_list this, int index, char *str);

/**
 * Returns the string at the specified position in the list.
 *
 * Returns:
 * NULL if index out of range
 * The string otherwise
 */
char *list_get(str_list this, int index);

/**
 * Returns whether the specified string is contained in the list.
 *
 * Returns:
 * 0 if str is not in the list
 * 1 if str is in the list
 */
int list_lookup(str_list this, char *str);

/**
 * Removes and returns the string at the specified position in the list.
 *
 * Returns:
 * NULL if index out of range
 * The string otherwise
 */
char *list_remove(str_list this, int index);

/**
 * Removes the first occurence of the specified string from the list.
 * 
 * Returns:
 * 0 if str is not in the list
 * 1 if str is in the list
 */
int list_remove_item(str_list this, char *str);

/**
 * Returns the number of strings in the list.
 */
int list_size(str_list this);

#endif