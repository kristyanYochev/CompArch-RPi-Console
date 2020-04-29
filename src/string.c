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