//
// Created by Hadar on 5/19/2024.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "set.c"
#include "set.h"

#define MAX_COMMAND_LENGTH 100
#define EXIT_COMMAND "stop"

int is_valid_set_name(char *set_name) {
    return (strlen(set_name) == 4 && set_name[0] == 'S' && set_name[1] == 'E' && set_name[2] == 'T' && set_name[3] >= 'A' && set_name[3] <= 'F');
}

int is_valid_number(char *num_str) {
    if (strcmp(num_str, "-1") == 0) { // Check for -1 explicitly
        return 1;
    }

    for (int i = 0; num_str[i] != '\0'; ++i) {
        if (!isdigit(num_str[i])) {
            return 0;
        }
    }
    int num = atoi(num_str);
    return (num >= 0 && num <= 127);
}

int validate_command(char *command) {
    if (command == NULL || strcmp(command, EXIT_COMMAND) == 0 || strcmp(command, "") == 0) {
        printf("Error: Command is NULL, exit, or empty\n");
        return 0;
    }

    char command_copy[256];
    strcpy(command_copy, command);

    char *cmd_name = strtok(command_copy, " ,"); // Updated delimiter to include spaces and commas
    if (cmd_name == NULL) {
        printf("Error: Command name is NULL\n");
        return 0;
    }

    if (strcmp(cmd_name, "read_set") == 0) {
        char *set_name = strtok(NULL, " ,");
        if (!is_valid_set_name(set_name)) {
            printf("Error: Invalid set name %s\n", set_name);
            return 0;
        }
        char *num_str;
        while ((num_str = strtok(NULL, " ,")) != NULL) {
            if (!is_valid_number(num_str)) {
                printf("Error: Invalid number %s\n", num_str);
                return 0;
            }
        }
        return 1;
    } else if (strcmp(cmd_name, "print_set") == 0) {
        char *set_name = strtok(NULL, " ,");
        if (!is_valid_set_name(set_name)) {
            printf("Error: Invalid set name %s\n", set_name);
            return 0;
        }
        return 1;
    } else if (strcmp(cmd_name, "union_set") == 0 ||
               strcmp(cmd_name, "intersect_set") == 0 ||
               strcmp(cmd_name, "sub_set") == 0 ||
               strcmp(cmd_name, "sym_diff_set") == 0) {
        char *set_name1 = strtok(NULL, " ,");
        char *set_name2 = strtok(NULL, " ,");
        char *set_name3 = strtok(NULL, " ,");
        if (!is_valid_set_name(set_name1) || !is_valid_set_name(set_name2) || !is_valid_set_name(set_name3)) {
            printf("Error: Invalid set names %s, %s, %s\n", set_name1, set_name2, set_name3);
            return 0;
        }
        return 1;
    }

    printf("Error: Invalid command name %s\n", cmd_name);
    return 0; // Invalid command
}

void execute_command(char *command, SetPtr sets[]){
    char *command_type, *args_start = "SET", *command_args, *set_name, *numbers_list;
    SetPtr sets_from_command_args[3];
    command_type = strtok(command, " ");
    command_args = command_type + strlen(command_type) + 1;
    remove_spaces_and_tabs(command_args);

    if(strcmp(command_type, "read_set") == 0){
        set_name = strtok(command_args, ",");
        numbers_list = (set_name + strlen(set_name) + 1);
        read_set(find_set_by_name(set_name, sets), numbers_list);
    }
    else if(strcmp(command_type, "print_set") == 0){
        set_name = command_args;
        print_set(find_set_by_name(set_name, sets));
    }
    else if(strcmp(command_type, "union_set") == 0){
        get_sets_from_command_args(command_args, sets, sets_from_command_args);
        union_set(sets_from_command_args[0], sets_from_command_args[1], sets_from_command_args[2]);
    }
    else if(strcmp(command_type, "intersect_set") == 0){
        get_sets_from_command_args(command_args, sets, sets_from_command_args);
        intersect_set(sets_from_command_args[0], sets_from_command_args[1], sets_from_command_args[2]);
    }
    else if(strcmp(command_type, "sub_set") == 0){
        get_sets_from_command_args(command_args, sets, sets_from_command_args);
        sub_set(sets_from_command_args[0], sets_from_command_args[1], sets_from_command_args[2]);
    }
    else if(strcmp(command_type, "symdiff_set") == 0){
        get_sets_from_command_args(command_args, sets, sets_from_command_args);
        sym_diff_set(sets_from_command_args[0], sets_from_command_args[1], sets_from_command_args[2]);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    Set* SETA, * SETB, * SETC, * SETD, * SETE, * SETF;

    SETA = init_set();
    SETB = init_set();
    SETC = init_set();
    SETD = init_set();
    SETE = init_set();
    SETF = init_set();

    SetPtr sets[6] = {SETA, SETB, SETC, SETD, SETE, SETF};

    printf("Enter command: ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);
    command[strcspn(command, "\n")] = '\0';  // Remove the newline character

    while(validate_command(command)){
        execute_command(command, sets);

        printf("Enter command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        command[strcspn(command, "\n")] = '\0';  // Remove the newline character
    }

    return 0;
}