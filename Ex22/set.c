//
// Created by Hadar on 5/19/2024.
//
#include <stdio.h>
#include <stdlib.h>

#include "set.h"

#define CAST_ASCII_NUMBER(number)  (number + '0')
#define MAX_VALUE_IN_LINE 16
#define NEW_LINE '\n'
#define EOL '\0'


void remove_spaces_and_tabs(char *str) {
    char* temp = str;
    do {
        while (*temp == ' ' || *temp == '\t') {
            ++temp;
        }
    } while (*str++ = *temp++);
}

// Helper function to find the set by name
Set* find_set_by_name(char* set_name, Set* sets[]) {
    if (strcmp(set_name, "SETA") == 0) return sets[0];
    if (strcmp(set_name, "SETB") == 0) return sets[1];
    if (strcmp(set_name, "SETC") == 0) return sets[2];
    if (strcmp(set_name, "SETD") == 0) return sets[3];
    if (strcmp(set_name, "SETE") == 0) return sets[4];
    if (strcmp(set_name, "SETF") == 0) return sets[5];
    return NULL; // Invalid set name
}

void reset_set(SetPtr set)
{
    unsigned char mask = {0};
    int i;

    for (i = 0; i < ARRAY_DATA_SIZE; ++i) {
        set->setData[i] = mask;
    }
}

SetPtr init_set()
{
    SetPtr set = (SetPtr)malloc(sizeof(Set));

    if(!set)
        return NULL;

    reset_set(set);

    return set;
}

char* convert_int_to_str(char* pStr, int number)
{
    if(number < 10)
    {
        *pStr++ = CAST_ASCII_NUMBER(number);
        return pStr;
    }

    pStr = convert_int_to_str(pStr, number / 10);
    *pStr++ = CAST_ASCII_NUMBER(number % 10);

    return pStr;
}

void print_set(SetPtr set)
{
    int byteIndex, bitIndex, countLineElements = 0;
    unsigned char* currByte;
    char* setStr;

    setStr = (char*)malloc(sizeof(char) * ARRAY_DATA_SIZE);
    char* currChar = setStr;

    *currChar++ = '(';

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++) {
        currByte = set->setData + byteIndex;

        for (bitIndex = 0; bitIndex < BYTE_SIZE; bitIndex++) {
            if(*currByte & (1 << bitIndex)){

                countLineElements++;
                if(countLineElements % MAX_VALUE_IN_LINE == 0)
                    *(currChar-1) = NEW_LINE;

                currChar = convert_int_to_str(currChar, byteIndex * BYTE_SIZE + bitIndex);
                *currChar++ = ' ';
                *currChar++ = ',';
            }
        }
    }

    if(*(currChar-1) == ',')
        currChar -=2;

    *currChar++ = ')';
    *currChar++ = EOL;

    printf("%s\n", setStr);
}

int read_set(SetPtr set, char* numbers_list)
{
    int byteIndex, bitIndex;
    char *number_str, *end_ptr;
    long int number_int;

    number_str = strtok(numbers_list, ",");
    while(number_str != NULL && strcmp(number_str, "-1") !=0)
    {
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

int union_set(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    int byteIndex;

    reset_set(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = setA->setData[byteIndex] | setB->setData[byteIndex];

    return 1;
}

int intersect_set(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    int byteIndex;

    reset_set(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = setA->setData[byteIndex] & setB->setData[byteIndex];

    return 1;
}

int sub_set(SetPtr originalSet, SetPtr subSet, SetPtr outputSet)
{
    int byteIndex;

    reset_set(outputSet);

    for (byteIndex = 0; byteIndex < ARRAY_DATA_SIZE; byteIndex++)
        outputSet->setData[byteIndex] = originalSet->setData[byteIndex] & ~subSet->setData[byteIndex];

    return 1;
}

int sym_diff_set(SetPtr setA, SetPtr setB, SetPtr outputSet)
{
    Set unionSetResult, intersectSetResult;

    reset_set(outputSet);

    union_set(setA, setB, &unionSetResult);
    intersect_set(setA, setB, &intersectSetResult);

    sub_set(&unionSetResult, &intersectSetResult, outputSet);

    return 1;
}


