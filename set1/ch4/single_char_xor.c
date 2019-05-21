#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "common.h"



int main( int argc, char *argv[] )
{
    if ( argc < 2 ) {
        fprintf( stderr, "Usage: %s <filename>\n", argv[0]);
        exit(0);
    }

    unsigned char inbuf[BUF_SIZE];
    size_t count;

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        fprintf( stderr, "Error open file: %s\n", argv[1]);
        exit(99);
    }

    count = readin_hexstr_from_file(fin, inbuf, BUF_SIZE);

    int lineno = 0;

    printf("%-3d: %3u ", lineno, inbuf[0]);

    for ( size_t i=1; i < count; i++) {
        if (!(i%8)) {
            lineno++;
            printf("\n%-3d: ", lineno);
        }
        printf("%3u ", inbuf[i]);
    }

    printf("\n");

    fclose(fin);

}
