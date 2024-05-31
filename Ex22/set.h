//
// Created by Hadar on 5/19/2024.
//

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdint.h>

#define MAX_NUM 127 // Define the maximum number in the set

#define BYTE_SIZE 8
#define END_OF_LIST (-1)
#define MAX_NUMBER 128
#define ARRAY_DATA_SIZE 16

typedef struct set
{
    unsigned char setData[ARRAY_DATA_SIZE];
} Set, * SetPtr;


void remove_spaces_and_tabs(char *str);
Set* find_set_by_name(char* set_name, Set* sets[]);
SetPtr init_set();
void print_set(SetPtr set);
int read_set(SetPtr set, char* numbers);
int union_set(SetPtr setA, SetPtr setB, SetPtr outputSet);
int intersect_set(SetPtr setA, SetPtr setB, SetPtr outputSet);
int sub_set(SetPtr originalSet, SetPtr subSet, SetPtr outputSet);
int sym_diff_set(SetPtr setA, SetPtr setB, SetPtr outputSet);

#endif /* SET_H */


