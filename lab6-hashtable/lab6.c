#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int main(int argc, char **argv)
{
    hashtable ht = hashtable_new(8);
    
    int i = 1;
    while (i < argc) {
        char *str = argv[i++];
        if (i < argc && strcmp(str, "-") == 0) {
            str = argv[i++];
            hashtable_remove(ht, str);
        }
        else if (i < argc && strcmp(str, "+") == 0) {
            str = argv[i++];
            hashtable_insert(ht, str);
        }
        else {
            hashtable_insert(ht, str);
        }
    }

    hashtable_print(ht);
    hashtable_free(ht);
}   