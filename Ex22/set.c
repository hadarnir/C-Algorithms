//
// Created by Hadar on 5/19/2024.
//

#include "set.h"

char* skip_spaces_and_tabs(char* str){
    while(*str == ' ' || *str == '\t')
        str++;
    return str;
}

// Helper function to find the set by name
Set* find_set_by_name(char* set_name, Set sets[]) {
    if (strcmp(set_name, "SETA") == 0) return &sets[0];
    if (strcmp(set_name, "SETB") == 0) return &sets[1];
    if (strcmp(set_name, "SETC") == 0) return &sets[2];
    if (strcmp(set_name, "SETD") == 0) return &sets[3];
    if (strcmp(set_name, "SETE") == 0) return &sets[4];
    if (strcmp(set_name, "SETF") == 0) return &sets[5];
    return NULL; // Invalid set name
}

void init_set(Set *set) {
    set->bits = 0; // Initialize all bits to 0
}

void add_num_to_set(Set *set, int num) {
    if (num >= 0 && num <= MAX_NUM) {
        set->bits |= ((__uint128_t)1 << num); // Set the bit at position num
    } else {
        printf("Error: Number out of range.\n");
    }
}

void remove_num_from_set(Set *set, int num) {
    if (num >= 0 && num <= MAX_NUM) {
        set->bits &= ~((__uint128_t)1 << num); // Clear the bit at position num
    } else {
        printf("Error: Number out of range.\n");
    }
}

int is_num_in_set(Set *set, int num) {
    if (num >= 0 && num <= MAX_NUM) {
        return (set->bits & ((__uint128_t)1 << num)) != 0; // Check if the bit at position num is set
    } else {
        printf("Error: Number out of range.\n");
        return 0; // Return false if number is out of range
    }
}

void read_set(char* command_args, Set sets[]){
    char *set_name, *numbers_list, *number_str, *endptr, *remaining_args;
    long int number_int;
    Set *set;

    set_name = strtok(command_args, ",");
    numbers_list = skip_spaces_and_tabs(set_name + strlen(set_name) + 1);
    set = find_set_by_name(set_name, sets);

    number_str = strtok(numbers_list, ",");
    while(number_str != NULL && strcmp(number_str, "-1") !=0)
    {
        number_int = strtol(number_str, &endptr, 10);
        // Check for conversion errors
        if (*endptr != '\0') {
            printf("Conversion error: %s\n", endptr);
            exit(1);
        }

        add_num_to_set(set, number_int);
        numbers_list = skip_spaces_and_tabs(number_str + strlen(number_str) + 1);
        number_str = strtok(numbers_list, ",");
    }
}

void print_set(Set *set) {
    printf("{ ");
    for (int i = 0; i < MAX_NUM; i++) {
        if (is_num_in_set(set, i)) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}

void print_set_wrapper(char* command_args, Set sets[]) {
    char *set_name;
    Set *set;
    set_name = command_args;
    set = find_set_by_name(set_name, sets);
    print_set(set);
}





