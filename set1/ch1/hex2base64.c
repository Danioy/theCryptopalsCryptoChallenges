/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hex2base64.h"

#define wrap_column 50

void
base64_encode (const char *restrict in, size_t inlen,
	       char *restrict out, size_t outlen)
{
    static const char b64str[64] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


    while (inlen && outlen)
    {
        *out++ = b64str[(in[0] >> 2) & 0x3f];
        if (!--outlen) break;

        *out++ = b64str[((in[0] << 4)
                    + (--inlen ? in[1] >> 4 : 0))
                    & 0x3f];
        if (!--outlen) break;

        *out++ = (inlen ? b64str[((in[1] << 2)
                    + (--inlen ? in[2] >> 6 : 0)) & 0x3f]
                    : '=');
        if (!--outlen) break;

        *out++ = inlen ? b64str[in[2] & 0x3f] : '=';
        if (!--outlen) break;

        if (inlen) inlen--;
        if (inlen) in += 3;
    }

    if (outlen) *out = '\0';
}


static void
wrap_write (const char *buffer, size_t len,
            size_t *current_column, FILE *out)
{
    size_t written;

    for (written = 0; written < len;)
    {
        size_t cols_remaining = wrap_column - *current_column;
        size_t to_write = MIN (cols_remaining, SIZE_MAX);
        to_write = MIN (to_write, len - written);

        if (to_write == 0)
          {
            if (fputc ('\n', out) == EOF) {
                perror("write error");
                abort();
            }
            *current_column = 0;
          }
        else
          {
            if (fwrite (buffer + written, 1, to_write, stdout) < to_write){
                perror("write error");
                abort();
            }
            *current_column += to_write;
            written += to_write;
          }
      }
}

static void
do_encode (FILE *in, FILE *out)
{
  size_t current_column = 0;
  char *inbuf, *outbuf;
  size_t sum;

  inbuf = malloc (BUF_SIZE);
  outbuf = malloc (BASE64_LENGTH(BUF_SIZE)+1);

  do
    {
      int n;

      sum = 0;
      do
        {
        n = fscanf(in, "%2hhx", inbuf+sum);
		if ( n > 0 ) sum += n;
        }
      while (!feof (in) && !ferror (in) && sum < BUF_SIZE);



      if (sum > 0)
        {
          /* Process input one block at a time.  Note that ENC_BLOCKSIZE
             is sized so that no pad chars will appear in output. */
          base64_encode (inbuf, sum, outbuf, BASE64_LENGTH(sum));

          wrap_write (outbuf, BASE64_LENGTH(sum),
                      &current_column, out);
        }
    }
  while (!feof (in) && !ferror (in) && sum == BUF_SIZE);

  /* When wrapping, terminate last line. */
  if (wrap_column && current_column > 0 && fputc ('\n', out) == EOF) {
      perror("write error");
      abort();
  }

  if (ferror (in)) {
      perror("read error");
      abort();
  }

  free (inbuf);
  free (outbuf);
}

int
main( void )
{
    do_encode(stdin, stdout);
    return 0;
}
