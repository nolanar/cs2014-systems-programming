#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "tokenizer.h"

struct tokenizer {
    char *str;
    char *delims;
    _Bool whitespace;
    int start;
    char *token;
};

_Bool isDelim(struct tokenizer *toke, char ch);

struct tokenizer *tokenizer_new(char *str, int start, char *delims) 
{
    struct tokenizer *toke = malloc(sizeof *toke);
    toke->str = str;
    toke->delims = delims;
    toke->whitespace = 1;
    toke->start = start;
    toke->token = malloc(sizeof *str);
    return toke;
}

char *next_token(struct tokenizer *toke)
//(char *str, int start, char *token)
{
    char *str = toke->str;
    int start = toke->start;
    char *token = toke->token;
    char ch = str[start];
    // ignore leading whitespace
    if (toke->whitespace) {
        while (ch != '\0' && isspace(ch)) {
            start++;
            ch = str[start];
        }
    }
    int i = 0;
    if (isDelim(toke, ch)) {
        token[i] = ch;
        i++;
    } else {
        while (ch != '\0' && !isDelim(toke, ch)) {
            token[i] = ch;
            i++;
            ch = str[start + i];
        }
    }
    token[i] = '\0';
    toke->start = ch == '\0' ? -1 : start + i;
    return token;
}

char *get_token(struct tokenizer *toke)
{
    return toke->token;
}

_Bool isDelim(struct tokenizer *toke, char ch)
{
    if (toke->whitespace && isspace(ch)) {
        return 1;
    }
    char *delims = toke->delims;
    char delim;
    int i = 0;
    do {
        delim = delims[i];
        if (ch == delim) {
            return 1;
        }
        i++;
    } while (delim != '\0');
    return 0;
}

int main()
{
    char *my_string = "Test string (-100+2.54-4)";
    char *delims = "()+-";
    struct tokenizer *toke = tokenizer_new(my_string, 0, delims);
    while(next_token(toke)[0] != '\0') {
        printf("%s\n", get_token(toke));
    }
    return 0;
}