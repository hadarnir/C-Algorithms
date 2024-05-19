//
// Created by Hadar on 5/19/2024.
//

#include "set.h"

void set_init(Set *set) {
    set->bits = 0; // Initialize all bits to 0
}

void set_add(Set *set, int num) {
    if (num >= 0 && num <= MAX_NUM) {
        set->bits |= ((__uint128_t)1 << num); // Set the bit at position num
    } else {
        printf("Error: Number out of range.\n");
    }
}

void set_remove(Set *set, int num) {
    if (num >= 0 && num <= MAX_NUM) {
        set->bits &= ~((__uint128_t)1 << num); // Clear the bit at position num
    } else {
        printf("Error: Number out of range.\n");
    }
}

int set_contains(Set *set, int num) {
    if (num >= 0 && num <= MAX_NUM) {
        return (set->bits & ((__uint128_t)1 << num)) != 0; // Check if the bit at position num is set
    } else {
        printf("Error: Number out of range.\n");
        return 0; // Return false if number is out of range
    }
}

void set_print(Set *set) {
    printf("{ ");
    for (int i = 0; i < MAX_NUM; i++) {
        if (set_contains(set, i)) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}



