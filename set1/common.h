/**
 *
 */

#ifndef TIGER_COMMON_H
#define TIGER_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#define Uint8_MAX (256)
#define BUF_SIZE (4096)

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


/**
 * Read in hex string from a file and then return the ASCII string and
 * how many ASCII bytes had been read.
 *
 * @param fin      [ptr to the FILE for input]
 * @param outbuf   [ptr to buf for store output content]
 * @param buf_size [The max size of buffer, which we will not read
 *                  more than the buffer. ]
 * @return size_t  [The actual bytes readed in. ]
 *
 */
size_t
readin_hexstr_from_file(FILE *fin, unsigned char *outbuf,
                        const size_t buf_size);

#endif      /* TIGER_COMMON_H */
