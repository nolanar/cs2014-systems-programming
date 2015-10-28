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

_Bool priv_isDelim(struct tokenizer *toke, char ch);
int priv_next_token(struct tokenizer *toke, char *token);

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

void tokenizer_free(struct tokenizer *toke)
{
    free(toke->token);
    free(toke);
}

char *next_token(struct tokenizer *toke)
{
    toke->start = priv_next_token(toke, toke->token);
    return toke->token;
}

char *peek_token(struct tokenizer *toke, char *next_token)
{
    priv_next_token(toke, next_token);
    return next_token;
}

char *get_token(struct tokenizer *toke)
{
    return toke->token;
}

int priv_next_token(struct tokenizer *toke, char *token)
{
    char *str = toke->str;
    int start = toke->start;
    char ch = str[start];
    // ignore leading whitespace
    if (toke->whitespace) {
        while (ch != '\0' && isspace(ch)) {
            start++;
            ch = str[start];
        }
    }
    int i = 0;
    if (priv_isDelim(toke, ch)) {
        token[i] = ch;
        i++;
    } else {
        while (ch != '\0' && !priv_isDelim(toke, ch)) {
            token[i] = ch;
            i++;
            ch = str[start + i];
        }
    }
    token[i] = '\0';
    start = ch == '\0' ? -1 : start + i;
    return start;
}

_Bool priv_isDelim(struct tokenizer *toke, char ch)
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