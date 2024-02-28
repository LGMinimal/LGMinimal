#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

long
toInteger(string value)
{
    long result = 0;
    size_t lenght = strlen(value);
    for(int i = 0; i < lenght; i++)
        {
            result += ((string)value)[i];
        }
    result += lenght * CONSTANT_TO_CALC_SIZE;
    return result;
}