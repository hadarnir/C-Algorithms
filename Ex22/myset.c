//
// Created by Hadar on 5/19/2024.
//

#include <stdio.h>
#include "set.c"
#include "set.h"



int main() {
    Set mySet;
    set_init(&mySet);
    set_add(&mySet, 5);
    set_add(&mySet, 10);
    set_add(&mySet, 64);

    printf("Set contents: ");
    set_print(&mySet);

    set_remove(&mySet, 10);
    printf("Set contents after removing 10: ");
    set_print(&mySet);

    return 0;
}