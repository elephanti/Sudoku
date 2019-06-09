#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "mainaux.h"


/**
 * Parse a game command from input stream. A command that receives an input and returns a command struct
containing the parsed command from the user.
 * @return {Command} The parsed command struct.
 */
command parse_command() {
    char user_input[MAX_COMMAND_LENGTH];
    char *token;
    int param_amount;
    char *pos;
    char *result;
    command received_command;

    /* Reached EOF - Exit! */
    if (feof(stdin)) {
        printf(EXIT_MSG);
        exit(-1);
    }

    /* User input as a whole row. */
    result = fgets(user_input, MAX_COMMAND_LENGTH, stdin);

    /* Check what caused the fgets to fail */
    if (result == NULL) {
        if (feof(stdin)) {
            printf(EXIT_MSG);
            exit(-1);
        }

        else if (ferror(stdin)){
            printf(FUNCTION_FAILED, "fgets");
        }
    }

    /* Skip the empty lines */
    while (strcmp(user_input, "\n") == 0 || strcmp(user_input,"\r\n") == 0) {
        result = fgets(user_input, MAX_COMMAND_LENGTH, stdin);

        /* Check what caused the fgets to fail */
        if (result == NULL) {
            if (feof(stdin)) {
                printf(EXIT_MSG);
                exit(-1);
            }

            else if (ferror(stdin)){
                printf(FUNCTION_FAILED, "fgets");
            }
        }
    }

    /* Split the input */
    token = strtok(user_input, " ");

    /* Remove trailing \n if it exists in the input */
    if ((pos=strchr(token, '\n')) != NULL)
        *pos = '\0';

    /* Parsing the command type.*/
    if (strcmp(token, "set") == 0) {
        received_command.command_chosen = set_move;
        param_amount = 3;
    } else if (strcmp(token, "hint") == 0) {
        received_command.command_chosen = hint_move;
        param_amount = 2;
    } else if (strcmp(token, "validate") == 0) {
        received_command.command_chosen = validate_move;
        return received_command;
    } else if (strcmp(token, "restart") == 0) {
        received_command.command_chosen = restart_move;
        return received_command;
    } else if (strcmp(token, "exit") == 0) {
        received_command.command_chosen = exit_game;
        return received_command;
    } else {
        /* Not a command! */
        received_command.command_chosen = invalid_type;
        return received_command;
    }


    received_command.param_amount = 0;
    token = strtok(NULL, " \t\r\n");

    /* Parse the command line arguments */
    while (token != NULL) {
        received_command.params[received_command.param_amount] = token[0] - '0';
        received_command.param_amount++;
        param_amount--;
        token = strtok(NULL, " \t\r\n");
    }

    /* Not enough arguments passed - command is invalid */
    if (param_amount > 0) {
        received_command.command_chosen = invalid_type;
    }

    return received_command;

}

/**
 * Test the parser
 * @return 0 = Success
 */
int parser_test() {
    command temp;
    temp = parse_command();
    printf("type:%d \n", temp.command_chosen);
    printf("param1:%d \n", temp.params[0]);
    printf("param2:%d \n", temp.params[1]);
    printf("param3:%d \n", temp.params[2]);


    return 0;
}