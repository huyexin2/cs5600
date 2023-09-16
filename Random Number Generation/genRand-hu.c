//
//  genRand-hu.c
//  
//
//  Created by Yexin Hu on 9/16/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Linear Congruential Generator (LCG) parameters
unsigned int seed = 0; // Initial seed (can be changed)
const unsigned int a = 1664525;
const unsigned int c = 1013904223;
const unsigned int m = 4294967296; // 2^32

// Function to generate a random integer in the specified range
int genRand(int min, int max) {
    seed = (a * seed + c) % m;
    return min + (seed % (max - min + 1));
}

int main(int argc, char *argv[]) {
    // Check the number of command-line arguments
    if (argc > 4) {
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
                FILE *file = fopen(filename,  "a");
                
                if (file == NULL) {
                    fprintf(stderr, "Failed to open the file for writing.\n");
                    return 1;
                }
                // Seed the random number generator with the current time
                srand((unsigned int)time(NULL));
                
                // Generate and write random integers to the file
                for (int i = 0; i < numRandomIntegers; i++) {
                    int randomInt = genRand(1, 100); // Change the range as needed
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
        
                FILE *file = fopen(filename,  "w");
                
                if (file == NULL) {
                    fprintf(stderr, "Failed to open the file for writing.\n");
                    return 1;
                }
                // Seed the random number generator with the current time
                srand((unsigned int)time(NULL));
                
                // Generate and write random integers to the file
                for (int i = 0; i < numRandomIntegers; i++) {
                    int randomInt = genRand(1, 100); // Change the range as needed
                    fprintf(file, "%d\n", randomInt);
                }
                
                // Close the file
                fclose(file);
                
                printf("Random integers written to '%s'.\n", filename);
                
                return 0;
            }
        }
    


