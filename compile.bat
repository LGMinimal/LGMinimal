@echo off

@rem COMPILE EXTERNAL BINARIES
cd src/utils/assets

    @rem utf_print
    g++ -o utf_print.exe utf-8.cpp
    move utf_print.exe ../../../bin/assets/utf_print.exe

cd ../../../

@rem COMPILE THE TRUE PROGRAM

gcc -g -ggdb -o program.exe main.c src/make.c src/make.h src/utils/error.c src/utils/error.h src/utils/output.h src/utils/output.c src/utils/colors.c src/utils/colors.h src/utils/types.c src/utils/types.h src/modules/lexical.c src/modules/lexical.h src/modules/parser.c src/modules/parser.h src/modules/parser/syntax.c src/modules/parser/syntax.h src/modules/parser/generate.c src/modules/parser/generate.h
move program.exe bin/lgcm.exe

pause > nul

cls

echo Compiled!