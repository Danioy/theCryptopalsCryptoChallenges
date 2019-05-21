/**
 * hex2base64, to read in a series of hex from either a file or stdin
 * then encode into  BASE64 string, either to a output file or
 * to stdout.
 *
 * Usage: hex2base64 [<filename in> [<filename out>]]
 *      if there is a <filename in>, the program will try to read
 *      from the file, otherwise will take in stdin string through
 *      command line pipe. example:
 *         > echo "49276d206b696c" | hex2base64
 *      if there is a <filename in>, the programing will try to
 *      send the result string to the said file, otherwise will
 *      display on the stdout.
 */

#ifndef HEX2BASE64_H
#define HEX2BASE64_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <error.h>

#define BUF_SIZE 4096

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define BASE64_LENGTH(in_len) (((( in_len ) + 2) / 3) * 4)

void base64_encode (const char *restrict in, size_t inlen,
            char *restrict out, size_t outlen);

static void
wrap_write (const char *buffer, size_t len,
            size_t *current_column, FILE *out);

static void
do_encode (FILE *in, FILE *out);

#endif     /* HEX2BASE64_H */
