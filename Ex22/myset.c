//
// Created by Hadar on 5/19/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.c"
#include "set.h"

#define MAX_COMMAND_LENGTH 100
#define EXIT_COMMAND "stop"

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

char* skip_spaces_and_tabs(char* str){
    while(*str == ' ' || *str == '\t')
        str++;
    return str;
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

        set_add(set, number_int);
        numbers_list = skip_spaces_and_tabs(number_str + strlen(number_str) + 1);
        number_str = strtok(numbers_list, ",");
    }
}

int validate_command(char *command){
    if(command == NULL || strcmp(command, EXIT_COMMAND) == 0)
        return 0;
    // TODO: Add more validations

    return 1;
}

void execute_command(char *command, Set sets[]){
    char *command_type, *args_start = "SET", *command_args;
    command_type = strtok(command, " ");
    command_args = skip_spaces_and_tabs(command_type + strlen(command_type) + 1);

    if(strcmp(command_type, "read_set") == 0){
        read_set(command_args, sets);
    }
    else if(strcmp(command_type, "print_set") == 0){

    }
    else if(strcmp(command_type, "union_set") == 0){

    }
    else if(strcmp(command_type, "intersect_set") == 0){

    }
    else if(strcmp(command_type, "sub_set") == 0){

    }
    else if(strcmp(command_type, "symdiff_set") == 0){

    }
}



int main() {
//    char command[MAX_COMMAND_LENGTH];
    char command[] = "read_set              SETA, 12, 32,   13,  32, -1\n";
    Set SETA, SETB, SETC, SETD, SETE, SETF;

    set_init(&SETA);
    set_init(&SETB);
    set_init(&SETC);
    set_init(&SETD);
    set_init(&SETE);
    set_init(&SETF);
    Set sets[6] = {SETA, SETB, SETC, SETD, SETE, SETF};


//    printf("Enter command: ");
//    fgets(command, MAX_COMMAND_LENGTH, stdin);

    while(validate_command(command)){
        command[strcspn(command, "\n")] = '\0';  // Remove the newline character
        execute_command(command, sets);
        set_print(&sets[0]);

        printf("Enter command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
    }

    return 0;
}