//
// Created by Hadar on 5/19/2024.
//

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdint.h>

#define MAX_NUM 127 // Define the maximum number in the set

typedef struct {
    __uint128_t bits;
} Set;

void init_set(Set *set);
void add_num_to_set(Set *set, int num);
void remove_num_from_set(Set *set, int num);
int is_num_in_set(Set *set, int num);
void print_set(Set *set);
void read_set(char* command_args, Set sets[]);

#endif /* SET_H */


