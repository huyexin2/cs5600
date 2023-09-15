//
//  HuYCommandLine.c
//  
//
//  Created by Yexin Hu on 9/12/23.
//

#include <stdio.h>

typedef void (*ConversionFunc)(char*);

// Compare string
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

// Convert the word to uppercase.
void lower2upper(char* c){
    while (*c != '\0'){
        if (*c >= 'a' && *c<= 'z'){
            *c = *c-32;
        }
        c++;
    }
}

// Convert the word to lowercase.
void upper2lower(char* c){
    while (*c != '\0'){
        if (*c >= 'A' && *c<= 'Z'){
            *c = *c+32;
        }
        c++;
    }
}

// Convert the first letter capitalized and all other characters of the word in lower case.
void cap(char* c){
    if (*c >= 'a' && *c<= 'z'){
        *c = *c-32;
    }
    c++;
    while (*c != '\0'){
        if (*c >= 'A' && *c<= 'Z'){
            *c = *c+32;
        }
        c++;
    }
}


int main(int argc, char* argv[])
{
    if (argc < 3) {
        printf("Please provide at least 3 arguments (program name, option, and at least one word)");
    }
    
    ConversionFunc conversionFunc = NULL;

    if (strcompre(argv[1], "-u") == 0) {
        conversionFunc = lower2upper;
    } else if (strcompre(argv[1], "-l") == 0) {
        conversionFunc = upper2lower;
    } else if (strcompre(argv[1], "-cap") == 0) {
        conversionFunc = cap;
    } else {
        return -1;
    }
        
    for (int i = 2; i < argc; i++){
        conversionFunc(argv[i]);
        printf("%s ", argv[i]);
    }

    printf("\n");
    return 0;
}