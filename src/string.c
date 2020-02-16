#include "string.h"

void byte_to_hex(unsigned char byte, char * output)
{
    const static char * hex = "0123456789ABCDEF";
    output[0] = hex[(byte >> 4) & 0xF];
    output[1] = hex[byte & 0xF];
    output[2] = '\0';
}
