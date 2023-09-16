/*
* randomNumber.c / Assignment Random Number Generation
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

#include <stdio.h>


/*
 * This function uses Linear Congruential Generator (LCG)
 * to generate random numbers.
 */
unsigned int seed = 0; // Initial seed (can be changed)
const unsigned int a = 1664525;
const unsigned int c = 1013904223;
const unsigned int m = 4294967296; // 2^32

int genRand(int min, int max) {
    seed = (a * seed + c) % m;
    return min + (seed % (max - min + 1));
}
