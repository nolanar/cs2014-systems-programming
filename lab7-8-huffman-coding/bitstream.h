#ifndef BITSTREAM
#define BITSTREAM

/**
 * Read a file bit by bit.
 */
typedef struct bitstream *bitstream;

/**
 * Constructs a new bitstream.
 * 
 * modes:
 * "r" read mode
 * "w" write mode
 */
 bitstream new_bitstream(char *filename, char *mode);

/**
 * Reads a bit from the bitstream.
 *
 * assert: must be in read mode.
 */
int read_bit(bitstream this);

/**
 * Writes a bit to the bitstream.
 *
 * assert: must be in write mode.
 */
int write_bit(bitstream this);

/**
 * Flushes any buffered bits to the bitstream.
 * This will pad with 0's to a byte offset.
 *
 * assert: must be in write mode.
 */
int write_bit(bitstream this);

/**
 * Returns whether the end of the file being read from has been reached.
 *
 * assert: must be in read mode. 
 */
int end_of_file(bitstream this);

/**
 * Attempts to close the underlying stream and free memory.
 *
 * Returns 1 if successful, 0 if failed to close.
 */
int close_bitstream(bitstream this);

#endif