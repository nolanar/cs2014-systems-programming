#include <stdlib.h>
#include <string.h>
#include "strlist.h"

struct node {
    struct node *next;
    char *str;
};

/* private functions */
struct node *node_new(char *str);
void priv_add_to_empty(struct list *this, char *str);
void priv_add_to_start(struct list *this, char *str);
void priv_add_to_end(struct list *this, char *str);
struct node *priv_get_node_at(struct list *this, int index);
struct node *priv_get_node_with(struct list *this, char *str);

struct node *node_new(char *str)
{
    struct node *this = malloc(sizeof *this);
    this->next = NULL;
    this->str = str;
    return this;
}

struct list *list_new()
{
    struct list *this = malloc(sizeof *this);
    this->size = 0;
    this->head = NULL;
    this->tail = NULL;
    return this;
}

void list_free(struct list *this)
{
    while (this->size != 0) {
        list_remove(this, 0);
    }
    free(this);
}

int list_add(struct list *this, int index, char *str)
{
    if (index < 0 || index > this->size) {
        return 0;
    }

    if (this->size == 0) {
        priv_add_to_empty(this, str);
    }
    else if (index == 0) {
        priv_add_to_start(this, str);
    }
    else if (index == this->size) {
        priv_add_to_end(this, str);
    }
    else {
        struct node *new_node = node_new(str);
        struct node *prev = priv_get_node_at(this, index - 1);
        struct node *next = prev->next;
        prev->next = new_node;
        new_node->next = next;
        this->size++;
    }
    return 1;
}

int list_set(struct list *this, int index, char *str)
{
    if (index < 0 || index >= this->size) {
        return 0;
    }

    priv_get_node_at(this, index)->str = str;
    return 1;
}

char *list_get(struct list *this, int index)
{
    if (index < 0 || index >= this->size) {
        return NULL;
    }

    return priv_get_node_at(this, index)->str;
}

int list_lookup(struct list *this, char *str)
{
    struct node *ptr = priv_get_node_with(this, str);
    return ptr == NULL ? 0 : 1;    
}

char *list_remove(struct list *this, int index)
{
    if (index < 0 || index >= this->size) {
        return NULL;
    }

    struct node *ptr = this->head;
    if (index == 0) {
        this->head = this->head->next;
    }
    else {
        struct node *prev = priv_get_node_at(this, index - 1);
        ptr = prev->next;
        prev->next = ptr->next;
        if (ptr == this->tail) {
            this->tail = prev;
        }
    }
    char *str = ptr->str;
    free(ptr);
    this->size--;
    return str;
}

int list_remove_item(struct list *this, char *str)
{
    if (this->size == 0) {
        return 0;
    }

    struct node *ptr = this->head;
    if (strcmp(this->head->str, str) == 0) {
        this->head = this->head->next;        
    }
    else {
        struct node *prev = ptr;
        ptr = ptr->next;
        while (ptr != NULL && strcmp(ptr->str, str) != 0) {
            prev = ptr;
            ptr = ptr->next;
        }
        if (ptr == NULL) {
            return 0;
        }
        prev->next = ptr->next;
        if (ptr == this->tail) {
            this->tail = prev;
        }
    }
    free(ptr);
    this->size--;
    return 1;
}

int list_size(struct list *this)
{
    return this->size;
}

/**
 * Private functions:
 */

void priv_add_to_empty(struct list *this, char *str)
{
    struct node *new_node = node_new(str);
    this->head = new_node;
    this->tail = new_node;
    this->size++;
}

void priv_add_to_start(struct list *this, char *str)
{
    struct node *new_node = node_new(str);
    new_node->next = this->head;
    this->head = new_node;    
    this->size++;
}

void priv_add_to_end(struct list *this, char *str)
{
    struct node *new_node = node_new(str);
    this->tail->next = new_node;
    this->tail = new_node;    
    this->size++;
}

struct node *priv_get_node_at(struct list *this, int index)
{
    struct node *ptr;
    if (index == this->size - 1) {
        ptr = this->tail;
    }
    else {
        ptr = this->head;
        for (int i = 0; i < index; i++) {
            ptr = ptr->next;
        }
    }
    return ptr;
}

struct node *priv_get_node_with(struct list *this, char *str)
{
    struct node *ptr;
    for (ptr = this->head; ptr != NULL; ptr = ptr->next) {
        if (strcmp(ptr->str, str) == 0) {
            return ptr;
        }
    }
    return NULL; 
}
