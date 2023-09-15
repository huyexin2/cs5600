/*
* HuY.CS5600.LearnC.c / Assignment Name
*
* Yexin Hu / CS5600 / Northeastern University
* Fall 2023 / Sep 8, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "mpg2km.h"

int main(){
    // proper case for mpg2kml
    printf("%f", mpg2kml(20));
    printf("\n");
    
    // negative input case for mpg2kml
    printf("%f", mpg2kml(-4));
    printf("\n");
    
    //proper case for mpg2lphm
    printf("%f", mpg2lphm(20));
    printf("\n");
    
    // negative input case for mpg2lphm
    printf("%f", mpg2lphm(-4));
    printf("\n");
    
    //proper case for kml2mpg
    printf("%f", lph2mpg(20));
    printf("\n");
    
    // negative input case for kml2mpg
    printf("%f", lph2mpg(-1));
    printf("\n");
}
