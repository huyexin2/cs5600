/*
* genRand-hu.c / Assignment Random Number Generation
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "randomNumber.h"

int main(int argc, char *argv[]) {
    initSeed();
    // Check the number of command-line arguments
    if (argc > 4 || argc < 3) {
        fprintf(stderr, "Usage: %s <number> <filename> <-a/-o>\n", argv[0]);
        return 1;
    }
    
    int numRandomIntegers = atoi(argv[1]);
    const char *filename = argv[2];
    if (argc == 4){
        if (strcmp(argv[3], "-a") != 0){
            fprintf(stderr, "Invalid mode. Use '-a' to append \n");
            return 1;
        } else {
            if (strcmp(argv[3], "-a") == 0){
                // Open the file with append mode
                FILE *file = fopen(filename,  "a");
                
                // Throw error when failed to open file
                if (file == NULL) {
                    fprintf(stderr, "Failed to open the file for writing.\n");
                    return 1;
                }
                // using time to generate seed for random number
                //srand((unsigned int)time(NULL));
                
                // Generate and write random integers to the file
                for (int i = 0; i < numRandomIntegers; i++) {
                    int randomInt = genRand(1, 100);
                    fprintf(file, "%d\n", randomInt);
                }
                
                // Close the file
                fclose(file);
                
                printf("Random integers written to '%s'.\n", filename);
                
                return 0;
            }
        }
    }
    
    if (argc == 3){
        // Open the file with write mode
        FILE *file = fopen(filename,  "w");
        
        // Throw error when failed to open file
        if (file == NULL) {
            fprintf(stderr, "Failed to open the file for writing.\n");
            return 1;
        }
        // using time to generate seed for random number
        //srand((unsigned int)time(NULL));
        
        // Generate and write random integers to the file
        for (int i = 0; i < numRandomIntegers; i++) {
            int randomInt = genRand(1, 100);
            fprintf(file, "%d\n", randomInt);
        }
        
        // Close the file
        fclose(file);
        
        printf("Random integers written to '%s'.\n", filename);
        
        return 0;
    }
}
    


