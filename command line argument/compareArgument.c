/*
* compareArgument.c /  Command Line Argument
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

#include <stdio.h>

// Compare command line input arguments.
int strcompre(char* str1, char* str2) {
    int flag = 0;
    while(*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            flag = -1;
        }
        str1++;
        str2++;
    }
    return flag;
}
