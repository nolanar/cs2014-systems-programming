#ifndef STRLIST
#define STRLIST

typedef struct list *strlist;

strlist list_new();

int list_add(strlist this, int index, char *str);

#endif