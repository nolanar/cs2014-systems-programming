
/**
 * Utility to tokenize strings
 */
typedef struct tokenizer *tokenizer;

/** 
 * Returns a new tokenizer object.
 *
 * note: This should be used when a new stack is required.
 */
struct tokenizer *tokenizer_new(char *str, int start, char *delims);



char *next_token(struct tokenizer *toke);

_Bool isDelim(struct tokenizer *toke, char ch);

char *get_token(struct tokenizer *toke);