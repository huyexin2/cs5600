/*
* HuYConnabdLine.c /  Command Line Argument
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

#include <stdio.h>
#include "letterConversion.h"
#include "compareArgument.h"

typedef void (*ConversionFunc)(char*);

int main(int argc, char* argv[])
{
    if (argc < 3) {
            printf("Error: Please provide at least 3 arguments (program name, option, and at least one word).\n");
            return -1;
        }
    ConversionFunc conversionFunc = NULL;

    if (strcompre(argv[1], "-u") == 0) {
        conversionFunc = lower2upper;
    } else if (strcompre(argv[1], "-l") == 0) {
        conversionFunc = upper2lower;
    } else if (strcompre(argv[1], "-cap") == 0) {
        conversionFunc = cap;
    } else {
        printf("Error: Please provide a vaild option: -l, -u, -cap.\n");
        return -1;
    }
        
    for (int i = 2; i < argc; i++){
        conversionFunc(argv[i]);
        printf("%s ", argv[i]);
    }

    printf("\n");
    return 0;
}

