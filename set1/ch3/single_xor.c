#include "common.h"
#include <math.h>
#include <ctype.h>

const unsigned char letter_frequency[26] = {
    'e', 't', 'a', 'o', 'i', 'n', 's', 'r', 'h', 'd', 'l', 'u', 'c',
    'm', 'f', 'y', 'w', 'g', 'p', 'b', 'v', 'k', 'x', 'q', 'j', 'z'
};

void letter_freq(const unsigned char *text, size_t textlen,
        double *freqtab, size_t tablen)
{

    size_t cnt_tab[tablen];
    memset(cnt_tab, 0, sizeof(size_t)*tablen);

    for (size_t i = 0; i < textlen; i++) {
        cnt_tab[(size_t)text[i]]++;
    }

    for (size_t i = 0; i < tablen; i++ ) {
        freqtab[i] = cnt_tab[i] / (double)textlen;
    }
}

void letter_count(const unsigned char *text, size_t textlen,
        int *counttab, size_t tablen)
{
    memset(counttab, 0, sizeof(int)*tablen);

    for (size_t i = 0; i < textlen; i++)
        counttab[(size_t)text[i]]++;
}

void insert_sort_ip_double(double *tab, size_t len, unsigned char *ref)
{
    double key;
    unsigned char refkey;
    size_t i, j;

    for ( i = 1; i < len; i++) {
        key = tab[i]; refkey = ref[i]; j = i - 1;

        while ( j >= 0 && tab[j] < key) {
            tab[j + 1] = tab[j];
            ref[j + 1] = ref[j];
            j--;
        }
        tab[j+1] = key; ref[j+1] = refkey;
    }
}

void insert_sort_ip_int(int *tab, size_t len, unsigned char *ref)
{
    int key;
    unsigned char refkey;
    size_t i, j;

    for ( i = 1; i < len; i++) {
        key = tab[i]; refkey = ref[i]; j = i - 1;

        while ( j >= 0 && tab[j] < key) {
            tab[j + 1] = tab[j];
            ref[j + 1] = ref[j];
            j--;
        }
        tab[j+1] = key; ref[j+1] = refkey;
    }
}

int main( void )
{
    /* used to store text */
    unsigned char inbuf[BUF_SIZE] = {0};

    unsigned char outbuf[BUF_SIZE] = {0};
    int keybuf[256] = {0};
    /* used to stroe text length, which return from readin func. */
    size_t n;
    /* used to store initial letter freq.*/
    double freq[256] = {0};

    n = readin_hexstr_from_file(stdin, inbuf, BUF_SIZE);

    printf("%I64d: %s", n,inbuf);

    letter_freq(inbuf, n, freq, 256);


    unsigned char tabref[256];
    for (size_t i = 0; i < 256; i++) tabref[i] = i;

    insert_sort_ip_double(freq, 256, tabref);

    unsigned char key;

    for (size_t j = 0; j < 7; j++) {
    for (size_t i = 0; i < 6; i++) {
        key = tabref[j] ^ letter_frequency[i];
        keybuf[key]++;
    }}


    for ( int i = 0; i < 256; i++) {
        if (keybuf[i] < 2 ) continue;
        else {
            printf("%d: ", i);
            for (size_t j = 0; j < BUF_SIZE; j++) {
                if (inbuf[j])
                outbuf[j] = inbuf[j] ^ i;
            }
            printf("%s\n", outbuf);
        }
    }

    return 0;

}
