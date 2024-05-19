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

}



int main() {
    char command[MAX_COMMAND_LENGTH];
    Set SETA, SETB, SETC, SETD, SETE, SETF;

    set_init(&SETA);
    set_init(&SETB);
    set_init(&SETC);
    set_init(&SETD);
    set_init(&SETE);
    set_init(&SETF);
    Set sets[6] = {SETA, SETB, SETC, SETD, SETE, SETF};

    printf("Enter command: ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    while(validate_command(command)){
        command[strcspn(command, "\n")] = '\0';  // Remove the newline character
        execute_command(command, sets);

        printf("Enter command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
    }

    return 0;
}