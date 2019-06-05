#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "mainaux.h"


/* A command that receives an input and returns a command struct
containing the parsed command from the user.*/
command parse_command() {
    char user_input[MAX_COMMAND_LENGTH];
    char *token;
    command received_command;
    int param_amount;

    /* User input as a whole row. */
    fgets(user_input, MAX_COMMAND_LENGTH, stdin);

    /* Reached EOF - Exit! */
    if (feof(stdin)) {
        printf(EXIT_MSG);
        exit(-1);
    }

    while (strcmp(user_input, "\n") == 0) {
        /* User input as a whole row. */
        fgets(user_input, MAX_COMMAND_LENGTH, stdin);

        /* Reached EOF - Exit! */
        if (feof(stdin)) {
            printf(EXIT_MSG);
            exit(-1);
        }
    }

    token = strtok(user_input, " ");


    /* Parsing the command type.*/
    if (strcmp(token, "set") == 0) {
        received_command.command_chosen = set_move;
        param_amount = 3;
    } else if (strcmp(token, "hint") == 0) {
        received_command.command_chosen = hint_move;
        param_amount = 2;
    } else if (strcmp(token, "validate\n") == 0) {
        received_command.command_chosen = validate_move;
        return received_command;
    } else if (strcmp(token, "restart\n") == 0) {
        received_command.command_chosen = restart_move;
        return received_command;
    } else if (strcmp(token, "exit\n") == 0) {
        received_command.command_chosen = exit_game;
        return received_command;
    } else {
        /* Not a command! */
        received_command.command_chosen = invalid_type;
        return received_command;
    }


    received_command.param_amount = 0;
    token = strtok(NULL, " \t\r\n");

    while (token != NULL) {
        received_command.params[received_command.param_amount] = token[0] - '0';
        received_command.param_amount++;
        param_amount--;
        token = strtok(NULL, " \t\r\n");
    }
    if (param_amount > 0) {
        received_command.command_chosen = invalid_type;
    }
    return received_command;


}


int parser_test() {
    command temp;
    temp = parse_command();
    printf("type:%d \n", temp.command_chosen);
    printf("param1:%d \n", temp.params[0]);
    printf("param2:%d \n", temp.params[1]);
    printf("param3:%d \n", temp.params[2]);


    return 0;
}