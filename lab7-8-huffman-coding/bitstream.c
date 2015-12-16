#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define CHAR_LEN CHAR_BIT

struct bitstream {
    FILE *file;
    unsigned char buffer;
    char buff_pos;
    char read;
    char write;
    int eof;
};

struct bitstream *new_bitstream(char *filename, char *mode)
{
    struct bitstream *this = malloc(sizeof *this);
    this->buffer = 0;
    this->buff_pos = CHAR_LEN - 1;
    this->eof = 0;
    if (strcmp(mode, "r") == 0) {
        this->file = fopen(filename, "r");
        this->read = 1;
        this->write = 0;
    }
    else if (strcmp(mode, "w") == 0) {
        this->file = fopen(filename, "w");
        this->read = 0;
        this->write = 1;
    }
    else {
        assert(0 && "not a valid bitstream mode");
    }
    return this;
}

int read_bit(struct bitstream *this)
{
    assert(this->read && "must be in read mode");
    int pos = this->buff_pos;
    /* buffer is empty if pos is CHAR_LEN - 1 */
    if (pos == CHAR_LEN - 1) {
        printf("in: %x\n", this->buffer = fgetc(this->file));
    }
    int bit = (this->buffer >> pos) & 1;
    this->buff_pos = (pos == 0 ? CHAR_LEN - 1 : pos - 1);
    return bit;
}

int write_bit(struct bitstream *this, int bit)
{
    assert(this->write && "must be in write mode");
    int pos = this->buff_pos;
    this->buffer = this->buffer | (bit << pos);
    /* if buffer full, put into file and clear buffer */
    if (pos == 0) {
        fputc(this->buffer, this->file);
        this->buffer = 0;
    }
    this->buff_pos = (pos == 0 ? CHAR_LEN - 1 : pos - 1);
    return bit;
}

void flush(struct bitstream *this)
{
    assert(this->write && "must be in write mode");
    /* buffer empty if pos is CHAR_LEN - 1 */
    if (this->buff_pos != CHAR_LEN - 1) {
        fputc(this->buffer, this->file);
        this->buffer = 0;
        this->buff_pos = CHAR_LEN - 1;
    }    
}

int end_of_file(struct bitstream *this)
{
    assert(this->read && "must be in read mode");
    /* if buffer empty and at end of byte file */
    return feof(this->file);
}

int close_bitstream(struct bitstream *this)
{
    if (!fclose(this->file)) {
        return 0;
    }
    free(this);
    return 1;
}
