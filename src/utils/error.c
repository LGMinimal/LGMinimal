#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "error.h"
#include "types.h"
#include "colors.h"

void lgcm(string msg);

Error 
newError() 
{
    return (Error) { lgcm };
}

void 
showFinalMessage() 
{
    Colorizer drawer = (Colorizer) { newColorize() };
    drawer.out.setColor(Red);
    printf(" x ");
    drawer.out.setColor(Reset);
    printf("compilation terminated.\n");
    exit(0);
}

void 
lgcm(string msg) 
{
    Colorizer drawer = (Colorizer) { newColorize() };
    drawer.out.setColor(Purple);
    printf("LGCM");
    drawer.out.setColor(Reset);
    printf(": ");
    drawer.out.setColor(Red);
    printf("fatal error");
    drawer.out.setColor(Reset);
    printf(": %s\n", msg);
    showFinalMessage();
}