//
// Created by Hadar on 6/1/2024.
//
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "validations.h"

#define EXIT_COMMAND "stop"

/**
 * Check if a given set name is valid.
 * Valid set names are in the format "SETX" where X is a letter from A to F.
 *
 * @param set_name The set name to validate.
 * @return 1 if the set name is valid, 0 otherwise.
 */
int is_valid_set_name(char *set_name) {
    return (strlen(set_name) == 4 && set_name[0] == 'S' && set_name[1] == 'E' && set_name[2] == 'T' && set_name[3] >= 'A' && set_name[3] <= 'F');
}

/**
 * Check if a given string represents a valid number.
 * Valid numbers are non-negative integers less than or equal to 127.
 *
 * @param num_str The string to check.
 * @return 1 if the string is a valid number, 0 otherwise.
 */
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

/**
 * Validate a command string.
 * Checks if the command is not NULL, not an empty string, and not the exit command.
 * Additionally, validates the command and its arguments based on the command type.
 *
 * @param command The command string to validate.
 * @return 1 if the command is valid, 0 otherwise.
 */
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
        char *last_num_str = NULL;  // Store the last number string encountered
        while ((num_str = strtok(NULL, " ,")) != NULL) {
            if (!is_valid_number(num_str)) {
                printf("Error: Invalid number %s\n", num_str);
                return 0;
            }
            last_num_str = num_str;  // Update the last number string
        }

        if (last_num_str == NULL || strcmp(last_num_str, "-1") != 0) {
            printf("Error: Last number should be -1 in read_set\n");
            return 0;
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
               strcmp(cmd_name, "symdiff_set") == 0) {
        char *set_name1 = strtok(NULL, " ,");
        char *set_name2 = strtok(NULL, " ,");
        char *set_name3 = strtok(NULL, " ,");
        char *extra_param = strtok(NULL, " ,");  // Check for extra parameters

        if (set_name1 == NULL || set_name2 == NULL || set_name3 == NULL || extra_param != NULL) {
            printf("Error: Invalid command parameters for %s\n", cmd_name);
            return 0;
        }

        if (!is_valid_set_name(set_name1) || !is_valid_set_name(set_name2) || !is_valid_set_name(set_name3)) {
            printf("Error: Invalid set names %s, %s, %s\n", set_name1, set_name2, set_name3);
            return 0;
        }

        return 1;
    }

    printf("Error: Invalid command name %s\n", cmd_name);
    return 0; // Invalid command
}