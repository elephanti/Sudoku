#ifndef SUDOKU_PARSER_H
#define SUDOKU_PARSER_H

#define TRUE 1
#define FALSE 0
#define MAX_COMMAND_LENGTH 1024

typedef enum Type {
    invalid_type, set_move, hint_move, validate_move, restart_move, exit_game
} command_type;


typedef struct comm {
    command_type command_chosen;
    int params[3];
    int param_amount;
} command;

int equals(char *str1, char *str2);

command parse_command();

#endif
