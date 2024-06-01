//
// Created by Hadar on 5/19/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

#define CAST_ASCII_NUMBER(number)  (number + '0')
#define MAX_VALUE_IN_LINE 16
#define NEW_LINE '\n'
#define EOL '\0'

/**
 * @brief Removes all spaces and tabs from the given string.
 *
 * This function modifies the input string to remove all spaces and tabs.
 *
 * @param str Pointer to the string to be modified.
 */
void remove_spaces_and_tabs(char *str) {
    char* temp = str;
    do {
        while (*temp == ' ' || *temp == '\t') {
            ++temp;
        }
    } while (*str++ = *temp++);
}

/**
 * @brief Finds a set by its name.
 *
 * This helper function searches for a set by its name and returns a pointer to the set if found.
 *
 * @param set_name Name of the set to find.
 * @param sets Array of set pointers to search within.
 * @return Pointer to the found set, or NULL if not found.
 */
SetPtr find_set_by_name(char* set_name, SetPtr sets[]) {
    if (strcmp(set_name, "SETA") == 0) return sets[0];
    if (strcmp(set_name, "SETB") == 0) return sets[1];
    if (strcmp(set_name, "SETC") == 0) return sets[2];
    if (strcmp(set_name, "SETD") == 0) return sets[3];
    if (strcmp(set_name, "SETE") == 0) return sets[4];
    if (strcmp(set_name, "SETF") == 0) return sets[5];
    return NULL; // Invalid set name
}

/**
 * @brief Extracts sets from command arguments.
 *
 * This function parses a command string to extract set names and finds the corresponding sets.
 *
 * @param command_args Command arguments containing set names.
 * @param sets Array of set pointers to search within.
 * @param sets_from_command_args Array to store pointers to the found sets.
 */
void get_sets_from_command_args(char* command_args, SetPtr sets[], SetPtr sets_from_command_args[]) {
    char* set_name;
    SetPtr set_ptr;

    set_name = strtok(command_args, ",");
    set_ptr = find_set_by_name(set_name, sets);
    sets_from_command_args[0] = set_ptr;

    command_args = (set_name + strlen(set_name) + 1);
    set_name = strtok(command_args, ",");
    set_ptr = find_set_by_name(set_name, sets);
    sets_from_command_args[1] = set_ptr;

    set_name = (set_name + strlen(set_name) + 1);
    set_ptr = find_set_by_name(set_name, sets);
    sets_from_command_args[2] = set_ptr;
}

/**
 * @brief Resets a set by clearing all its elements.
 *
 * This function sets all bits in the set to 0.
 *
 * @param set Pointer to the set to be reset.
 */
void reset_set(SetPtr set) {
    unsigned char mask = {0};
    int i;

    for (i = 0; i < ARRAY_DATA_SIZE; ++i) {
        set->setData[i] = mask;
    }
}

/**
 * @brief Initializes a new set.
 *
 * This function allocates memory for a new set, resets it, and returns a pointer to it.
 *
 * @return Pointer to the newly initialized set, or NULL if memory allocation fails.
 */
SetPtr init_set() {
    SetPtr set = (SetPtr)malloc(sizeof(Set));

    if (!set)
        return NULL;

    reset_set(set);

    return set;
}

/**
 * @brief Converts an integer to a string representation.
 *
 * This function converts an integer to a string and stores it in the provided buffer.
 *
 * @param pStr Pointer to the buffer to store the string representation.
 * @param number The integer to convert.
 * @return Pointer to the next position in the buffer after the converted string.
 */
char* convert_int_to_str(char* pStr, int number) {
    if (number < 10) {
        *pStr++ = CAST_ASCII_NUMBER(number);
        return pStr;
    }

    pStr = convert_int_to_str(pStr, number / 10);
    *pStr++ = CAST_ASCII_NUMBER(number % 10);

    return pStr;
}

/**
 * @brief Prints the elements of a set.
 *
 * This function prints all elements of the given set, formatting the output for readability.
 *
 * @param set Pointer to the set to print.
 */
void print_set(SetPtr set) {
    int byteIndex, bitIndex, countLineElements = 0;
    unsigned char* currByte;
    char* setStr;

    setStr = (char*)malloc(sizeof(char) * ARRAY_DATA_SIZE * BYTE_SIZE + 3); // Adjust the size for safety
    char* currChar = setStr;

    *currChar++ = '(';

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++) {
        currByte = set->setData + byteIndex;

        for (bitIndex = 0; bitIndex < BYTE_SIZE; bitIndex++) {
            if (*currByte & (1 << bitIndex)) {
                countLineElements++;
                if (countLineElements % MAX_VALUE_IN_LINE == 0)
                    *(currChar - 1) = NEW_LINE;

                currChar = convert_int_to_str(currChar, byteIndex * BYTE_SIZE + bitIndex);
                *currChar++ = ' ';
                *currChar++ = ',';
            }
        }
    }

    if (countLineElements == 0) {
        // No elements in the set
        *currChar++ = ')';
        *currChar++ = EOL;
    } else {
        if (*(currChar - 1) == ',')
            currChar -= 2;

        *currChar++ = ')';
        *currChar++ = EOL;
    }

    printf("%s\n", setStr);
    free(setStr); // Don't forget to free the allocated memory
}


/**
 * @brief Reads a list of numbers and adds them to the set.
 *
 * This function parses a comma-separated list of numbers and sets the corresponding bits in the set.
 *
 * @param set Pointer to the set to modify.
 * @param numbers_list Comma-separated list of numbers to add to the set.
 * @return 1 on success.
 */
int read_set(SetPtr set, char* numbers_list) {
    int byteIndex, bitIndex;
    char *number_str, *end_ptr;
    long int number_int;

    number_str = strtok(numbers_list, ",");
    while (number_str != NULL && strcmp(number_str, "-1") != 0) {
        number_int = strtol(number_str, &end_ptr, 10);
        // Check for conversion errors
        if (*end_ptr != '\0') {
            printf("Conversion error: %s\n", end_ptr);
            exit(1);
        }

        byteIndex = number_int / BYTE_SIZE;
        bitIndex = number_int - byteIndex * BYTE_SIZE;

        set->setData[byteIndex] |= (1 << bitIndex);

        numbers_list = (number_str + strlen(number_str) + 1);
        number_str = strtok(numbers_list, ",");
    }
    return 1;
}

/**
 * @brief Computes the union of two sets.
 *
 * This function computes the union of two sets and stores the result in the output set.
 *
 * @param setA Pointer to the first set.
 * @param setB Pointer to the second set.
 * @param outputSet Pointer to the set to store the result.
 * @return 1 on success.
 */
int union_set(SetPtr setA, SetPtr setB, SetPtr outputSet) {
    int byteIndex;

    reset_set(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = setA->setData[byteIndex] | setB->setData[byteIndex];

    return 1;
}

/**
 * @brief Computes the intersection of two sets.
 *
 * This function computes the intersection of two sets and stores the result in the output set.
 *
 * @param setA Pointer to the first set.
 * @param setB Pointer to the second set.
 * @param outputSet Pointer to the set to store the result.
 * @return 1 on success.
 */
int intersect_set(SetPtr setA, SetPtr setB, SetPtr outputSet) {
    int byteIndex;

    reset_set(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = setA->setData[byteIndex] & setB->setData[byteIndex];

    return 1;
}

/**
 * @brief Computes the difference of two sets.
 *
 * This function computes the difference of the original set and the sub set, storing the result in the output set.
 *
 * @param originalSet Pointer to the original set.
 * @param subSet Pointer to the sub set.
 * @param outputSet Pointer to the set to store the result.
 * @return 1 on success.
 */
int sub_set(SetPtr originalSet, SetPtr subSet, SetPtr outputSet) {
    int byteIndex;

    reset_set(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = originalSet->setData[byteIndex] & ~subSet->setData[byteIndex];

    return 1;
}

/**
 * @brief Computes the symmetric difference of two sets.
 *
 * This function computes the symmetric difference of two sets and stores the result in the output set.
 *
 * @param setA Pointer to the first set.
 * @param setB Pointer to the second set.
 * @param outputSet Pointer to the set to store the result.
 * @return 1 on success.
 */
int sym_diff_set(SetPtr setA, SetPtr setB, SetPtr outputSet) {
    Set unionSetResult, intersectSetResult;

    reset_set(outputSet);

    union_set(setA, setB, &unionSetResult);
    intersect_set(setA, setB, &intersectSetResult);

    sub_set(&unionSetResult, &intersectSetResult, outputSet);

    return 1;
}
