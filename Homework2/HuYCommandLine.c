//
//  HuYCommandLine.c
//  
//
//  Created by Yexin Hu on 9/12/23.
//

#include <stdio.h>


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

void lower2upper(char* c){
    while (*c != '\0'){
        if (*c >= 'a' && *c<= 'z'){
            *c = *c-32;
        }
        c++;
    }
}

void upper2lower(char* c){
    while (*c != '\0'){
        if (*c >= 'A' && *c<= 'Z'){
            *c = *c+32;
        }
        c++;
    }
}


int main(int argc, char* argv[])
{
    
    if(strcompre(argv[1], "-u") == 0){
        for (int i = 2; i < argc; i++){
            lower2upper(argv[i]);
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    if(strcompre(argv[1], "-l") == 0){
        for (int i = 2; i < argc; i++){
            upper2lower(argv[i]);
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    
    return 0;
}

