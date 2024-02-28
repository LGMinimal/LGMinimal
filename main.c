#include <stdio.h>
#include "src/make.h"
#include "src/utils/error.h"
#include "src/utils/output.h"
#include "src/utils/types.h"
#include "src/utils/colors.h"

#define COMMANDS_LENGHT 2

int
main(int argc, char *args[]) 
{
    Output output = (Output) { newError() };
    Colorizer color = (Colorizer) { newColorize() };

    if( argc == 1 )
        /*->*/ output.errors.lgcm("no input of commands to be executed. If in doubt, use: lgcm help");

    const string command = args[1];
    switch(toInteger(command)) 
        {
            case 500528: 
                {

                    break;
                }
            case 400425:
                {
                    printf("Hello guest!\n");
                    printf("If you don't already know us, we  are from the LG-Ecosystem team.\n");
                    printf("We crate and develop incredible tools for your everyday life.\n\n");
                    printf("Comamnds:\n");
                    char commands[COMMANDS_LENGHT][2][100] = {
                        {
                            "build",
                            "Build your app at a executable file."
                        },
                        {
                            "help",
                            "Need help? Look here!"
                        }
                    };
                    for(char i = 0; i < COMMANDS_LENGHT; i++)
                        {
                            color.out.setColor(Purple);
                            printf("%s:\n", commands[i][0]);
                            color.out.setColor(Reset);
                            printf("\t- %s\n", commands[i][1]);
                        }

                    break;
                }
            default: 
                {

                }
        }

    return 0;
}