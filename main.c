#include <stdio.h>
#include <stdlib.h>
#include "src/utils/output.h"
#include "src/utils/colors.h"
#include "src/utils/error.h"
#include "src/utils/types.h"
#include "src/make.h"

#define COMMANDS_LENGHT 2
#ifdef _WIN32
#define SLASH_PATH '\\'
#include <direct.h>
#include <string.h>
#define GetCurrentDir _getcwd
string
getCwd() {
    char cwd[1024];
    if( GetCurrentDir(cwd, sizeof(cwd)) != NULL ) 
        {
            return strdup (cwd);
        }
    return "";
}
#else
#define SLASH_PATH '/'
#include <unistd.h>
#include <string.h>
#define GetCurrentDir getcwd
string
getCwd()
{
    char cwd[1024];
    if( GetCurrentDir(cwd, sizeof(cwd)) != NULL ) 
        {
            return strdup (cwd);
        } 
    return "";
}
#endif

int
main(int argc, string args[]) 
{
    Output output = (Output) { newError () };
    Colorizer color = (Colorizer) { newColorize () };

    if( argc == 1 )
        /*->*/ output.errors.lgcm ("no input of commands to be executed. If in doubt, use: lgcm help");

    string cwd = getCwd ();
    const string command = args[1];
    switch(toInteger (command)) 
        {
            case 500528: 
                {
                    string main = NULL;
                    vec *files = Vec (TString);
                    for( int i = 2; i < argc; i++ )
                        {
                            string current = args[i];
                            if( main == NULL )  
                                {
                                    main = (string)malloc (sizeof(char) * strlen (current));
                                    sprintf (main, "%s", current);
                                }
                            push (files, current);
                        }
                    for( int i = 0; i < files->length; i++ ) 
                        {
                            string file = (string)pull (files, i);
                            printf ("%d. arquivo: %s\n", i, file);
                        }

                    if( files->length == 0 )
                        /*->*/ output.errors.lgcm("provide files to be compiled.");

                    string mainFile = pull (files, 0);
                    if(! endsWith (mainFile, ".lgm")  )
                        /*->*/ output.errors.lgcm("this file is invalid.");

                    string format = (string)malloc(sizeof (char) * ( strlen (cwd) + strlen (mainFile) + 2 ));
                    sprintf(format, "%s%c%s", cwd, SLASH_PATH, mainFile);
                    FILE *file = fopen (format, "r");
                    make (file);

                    break;
                }
            case 400425:
                {
                    printf ("Hello guest!\n");
                    printf ("If you don't already know us, we  are from the LG-Ecosystem team.\n");
                    printf ("We crate and develop incredible tools for your everyday life.\n\n");
                    printf ("Comamnds:\n");
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
                            color.out.setColor (Purple);
                            printf ("%s:\n", commands[i][0]);
                            color.out.setColor (Reset);
                            printf ("\t- %s\n", commands[i][1]);
                        }

                    break;
                }
            default: 
                {
                    output.errors.lgcm ("this command was not found. If in doubt, use: lgcm help");
                }
        }

    free (command);
    free (cwd);
    return 0;
}