#include "string.h"

void byte_to_hex(unsigned char byte, char * output)
{
    const static char * hex = "0123456789ABCDEF";
    output[0] = hex[(byte >> 4) & 0xF];
    output[1] = hex[byte & 0xF];
    output[2] = '\0';
}

void byte_to_bin(unsigned char byte, char * output)
{
    for (int i = 0; i < 8; i++)
    {
        output[i] = ((byte & (1 << i)) == 0) ? '0' : '1';
    }
    output[8] = '\0';
}

char * strcpy(char * dst, const char * src)
{
    unsigned int i;
    for (i = 0; src[i] != '\0'; i++)
    {
        dst[i] = src[i];
    }

    dst[i] = '\0';
    return dst;
}

void itoa(char * src, int number, int length)
{
    int i;
    for (i = 1; i <= length; i++)
    {
        src[length - i] = (number % 10) + '0';
        number /= 10;
    }

    src[i - 1] = '\0';
}
