#include "colors.h"
#include "stdio.h"
#if _WIN32 
#include <windows.h>
void draw(colors color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (color)
        {
            case Purple:
                SetConsoleTextAttribute(hConsole, 5);
                break;
            case Blue:
                SetConsoleTextAttribute(hConsole, 1);
                break;
            case Green:
                SetConsoleTextAttribute(hConsole, 2);
                break;
            case Yellow:
                SetConsoleTextAttribute(hConsole, 6);
            case Red:
                SetConsoleTextAttribute(hConsole, 4);
                break;
            case Cyan:
                SetConsoleTextAttribute(hConsole, 11);
                break;
            default:
                if( color == White || color == Reset) {
                    SetConsoleTextAttribute(hConsole, 7);
                }
                break;
        }
}
#else 
#define ANSI_RESET   "\x1b[0m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_PURPLE "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"
void draw(colors color) {
    switch(color)
        {
            case Purple: 
                printf(ANSI_PURPLE);
                break;
            case Yellow: 
                printf(ANSI_YELLOW);
                break;
            case Blue: 
                printf(ANSI_BLUE);
                break;
            case Green: 
                printf(ANSI_GREEN);
                break;
            case Red: 
                printf(ANSI_RED);
                break;
            case White: 
                printf(ANSI_WHITE);
                break;
            case Cyan: 
                printf(ANSI_CYAN);
                break;
            case Reset: 
                printf(ANSI_RESET);
                break;
        }
}
#endif

Colorize 
newColorize() 
{
    return (Colorize) { draw };
}