#include <stdio.h>
#include "error.h"
#include "types.h"

Func 
evoke(string str) 
{
    long parsed = toInteger (str);
    switch(parsed) 
        {
            case 500554: 
                {
                    return (Func) newError;
                    break;
                }
        }
}