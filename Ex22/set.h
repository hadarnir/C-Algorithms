//
// Created by Hadar on 5/19/2024.
//

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdint.h>

#define MAX_NUM 128 // Define the maximum number in the set

typedef struct {
    __uint128_t bits;
} Set;

void set_init(Set *set);
void set_add(Set *set, int num);
void set_remove(Set *set, int num);
int set_contains(Set *set, int num);
void set_print(Set *set);

#endif /* SET_H */


