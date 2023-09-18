/*
* letterConversion.c /  Command Line Argument
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/


#include <stdio.h>

// Convert the word to uppercase.
void lower2upper(char* c){
    // Until the pointer reaches the end of string
    while (*c != '\0'){
        // char between a - z
        if (*c >= 'a' && *c<= 'z'){
            *c = *c-32;
        }
        c++;
    }
}

// Convert the word to uppercase.
void upper2lower(char* c){
    // Until the pointer reaches the end of string
    while (*c != '\0'){
        // char between A-Z
        if (*c >= 'A' && *c<= 'Z'){
            *c = *c+32;
        }
        c++;
    }
}

// Convert the first letter capitalized and all other characters of the word in lower
void cap(char* c){
    // Convert the first char
    if (*c >= 'a' && *c<= 'z'){
        *c = *c-32;
    }
    c++;
    // Until the pointer reaches the end of string
    while (*c != '\0'){
        if (*c >= 'A' && *c<= 'Z'){
            *c = *c+32;
        }
        c++;
    }
}
