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
        print_set_wrapper(command_args, sets);
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
    char *command;
    char command1[] = "read_set SETA, 12, 11,   7,  32, -1\n";
    char command2[] = "read_set SETB, 12, 13, 55,  1, -1\n";
    char command3[] = "union_set SETA, SETB, SETC\n";
//    char command3[] = "print_set SETA";
    Set SETA, SETB, SETC, SETD, SETE, SETF;

    init_set(&SETA);
    init_set(&SETB);
    init_set(&SETC);
    init_set(&SETD);
    init_set(&SETE);
    init_set(&SETF);
    Set sets[6] = {SETA, SETB, SETC, SETD, SETE, SETF};


    command1[strcspn(command1, "\n")] = '\0';  // Remove the newline character
    execute_command(command1, sets);
    print_set(&sets[0]);

    command2[strcspn(command2, "\n")] = '\0';  // Remove the newline character
    execute_command(command2, sets);
    print_set(&sets[1]);

    command3[strcspn(command3, "\n")] = '\0';  // Remove the newline character
    execute_command(command3, sets);



//    printf("Enter command: ");
//    fgets(command, MAX_COMMAND_LENGTH, stdin);

//    while(validate_command(command)){
//        command[strcspn(command, "\n")] = '\0';  // Remove the newline character
//        execute_command(command, sets);
//        print_set(&sets[0]);

//        printf("Enter command: ");
//        fgets(command, MAX_COMMAND_LENGTH, stdin);
//    }

    return 0;
}