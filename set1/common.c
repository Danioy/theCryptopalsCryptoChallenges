#include "common.h"


size_t
readin_hexstr_from_file(FILE *fin, unsigned char *outbuf,
    const size_t buf_size)
{
    size_t sum = 0;
    int n;

    do {
        n = fscanf(fin, "%2hhx", outbuf+sum);
        if ( n > 0 ) sum += n;
    } while ( !feof(fin) && !ferror(fin) && sum < buf_size);

    if (ferror(fin)) {
        fprintf( stderr, "Error on reading file: %s\n", strerror(errno));
        exit(99);
    }

    return sum;
}
