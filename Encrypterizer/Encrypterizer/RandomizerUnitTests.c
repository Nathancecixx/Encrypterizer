#define _CRT_SECURE_NO_WARNINGS
//Liam Cabarle - Randomizer Module
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h> //used for checking upper, lower, and digit
#include "Randomizer.h"
#include "RandomizerUnitTests.h"

//checks for uppercase letters and counts how many there are
void testUppercaseLetters() {
    unsigned char key[16];
    generateRandomKey(key, sizeof(key));
    //letter count
    int hasUppercase = 0;
    //goes through array and counts how many uppercase letters there are
    for (size_t i = 0; i < sizeof(key); i++) {
        if (isupper(key[i])) {
            hasUppercase++;
        }
    }
    //no uppercase letters = error
    if (!hasUppercase) {
        printf("Error: Key does not have an uppercase letter\n");
    }
    else {
        printf("Test passed! The key has %d uppercase letters\n", hasUppercase);
    }
}
//checks for lowercase letters and counts how many there are
void testLowercaseLetters() {
    unsigned char key[16];
    generateRandomKey(key, sizeof(key));
    //letter counter
    int hasLowercase = 0;
    //goes through array and counts the lowercase letters
    for (size_t i = 0; i < sizeof(key); i++) {
        if (islower(key[i])) {
            hasLowercase++;
        }
    }
    //no lowercase letters = error
    if (!hasLowercase) {
        printf("Error: Key does not have a lowercase letter\n");
    }
    else {
        printf("Test passed! The key has %d lowercase letters\n", hasLowercase);
    }
}
//checks for digits and counts how many there are
void testDigits() {
    unsigned char key[16];
    generateRandomKey(key, sizeof(key));
    //digit counter
    int hasDigit = 0;
    //iterates through the array and counts the digits
    for (size_t i = 0; i < sizeof(key); i++) {
        if (isdigit(key[i])) {
            hasDigit++;
        }
    }
    //no digits = error
    if (!hasDigit) {
        printf("Error: Key does not have digits\n");
    }
    else {
        printf("Test passed! The key has %d digits\n", hasDigit);
    }
}

//This unit test works, 
//but is not showing the right result because srand() is seeding the same current time
//the generated keys are all the same because they're seeded within the same time
//void testSrand() {    
//    unsigned char key1[16];
//    unsigned char key2[16];
//    srand(time(NULL));
//    generateRandomKey(key1, sizeof(key1) - 1);
//    key1[sizeof(key1) - 1] = '\0';
//    printf("This is key 1: %s\n", key1);
//    srand(time(NULL));
//    generateRandomKey(key2, sizeof(key2) - 1);
//    key2[sizeof(key2) - 1] = '\0';
//    printf("This is key 2: %s\n", key2);
//
//    if (memcmp(key1, key2, sizeof(key1)) == 0) {
//        printf("Error: Keys generated are the same\n");
//    }
//    else {
//        printf("Test passed! Keys are different\n");
//    }
//}

void testRandModulo3() {
    int counts[3] = { 0 };
    //makes choices 100 times to check if random numbers are chosen
    for (int i = 0; i < 100; i++) {
        int choice = rand() % 3;
        counts[choice]++;
    }
    //if 0 is chosen
    if (counts[0] <= 0) {
        printf("Error: rand() %% 3 never returns 0\n");
    }
    else {
        printf("Test passed. 0 was randomly chosen\n");
    }
    //if 1 is chosen
    if (counts[1] <= 0) {
        printf("Error: rand() %% 3 never returns 1\n");
    }
    else {
        printf("Test passed. 1 was randomly chosen\n");
    }
    //if 2 is chosen
    if (counts[2] <= 0) {
        printf("Error: rand() %% 3 never returns 2\n");
    }
    else {
        printf("Test passed. 2 was randomly chosen\n");
    }
}
//checks if the array was filled
void testArrayFill() {
    //empty array
    unsigned char key[16] = { 0 };

    generateRandomKey(key, sizeof(key));
    //goes through the array
    for (size_t i = 0; i < sizeof(key); i++) {
        //if array is empty = error
        if (key[i] == 0) {
            printf("Array was not filled\n");
            exit(EXIT_FAILURE);
        }
        else { //array is filled and it prints the array
            printf("Test passed. Array was filled\n");
            printf("Array: ");
            for (size_t i = 0; i < sizeof(key); i++) {
                printf("%c", key[i]);
            }
            exit(EXIT_SUCCESS);
        }
    }
}