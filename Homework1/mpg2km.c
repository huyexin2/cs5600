/*
* mpg2km.c / Assignment 1
*
* Yexin Hu / CS5600 / Northeastern University
* Fall 2023 / Sep 8, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>

/*
 * This function takes miles per gallon as an argument
 * and returns the equivalent kilometers per liter.
 */
float mpg2kml(float mpg){
    if (mpg < 0){
        printf("error: input argument cannot be less than 0");
        return -1;
    }
    float kml = mpg * 0.425144;
    return kml;
}

/*
 * This function takes miles per gallon as an argument
 * and returns the equivalent number of liter per 100 kilometers
 */
float mpg2lphm(float mpg){
    if(mpg < 0){
        printf("error: input argument cannot be less than 0");
        return -1;
    }
    float lphm = 235.215 / mpg;
    return lphm;
}

/*
 * This function takes the kilometers per liter as an argument
 * and returns miles per gallon
 */
float lph2mpg(float lkm){
    if(lkm <= 0){
        printf("error: input argument cannot be less or equal to 0");
        return -1;
    }
    float mpg = 235.215/lkm;
    return mpg;
}
