#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) < (b) ? (b) : (a))

size_t
hexstr2buf(const char *str, size_t str_len, char *outbuf, size_t buf_size)
{
    size_t sum = 0;
    int n;
    for ( size_t i = 0; i < str_len || i < buf_size*2; i+=2) {
        n = sscanf(&str[i], "%2hhx", outbuf+sum);
        if ( n > 0) sum += n;
        else break;
    }
    return sum;
}


int main( void )
{
    char s1[] = "1c0111001f010100061a024b53535009181c";
    char buf1[4096];
    char s2[] = "686974207468652062756c6c277320657965";
    char buf2[4096];
    char res[4096];
    size_t i;

    size_t n = hexstr2buf(s1, strlen(s1), buf1, 4096);
    size_t m = hexstr2buf(s2, strlen(s2), buf2, 4096);
    for ( i = 0; i < 4096; i++)
        res[i] = buf1[i] ^ buf2[i];
    for ( i = 0; i < MAX(n, m); i++)
        printf("%.2x", res[i]);
    printf("\n");
}
