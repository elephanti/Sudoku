/*created by Yair on 3.6.19*/
#include "parser.h"
#include "game.h"
#include "mainaux.h"
#include "solver.h"

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    struct Cell **board, **board_solution;
    int num_of_hints;
    int seed;
    int i;
    int has_won;
    command user_input;

    if (argc != 2) {
        printf("ERROR: Seed was not passed! Exiting.");
        return -1;
    }

    seed = atoi(argv[1]);
    srand(seed);

    if (get_cells_number_input(&num_of_hints) == 0) {
        printf("Error: not a number\n");
        printf(EXIT_MSG);
        return SUCCESS;
    }

    /* Initializing the game */
    board = create_empty_board(GRID_HEIGHT, GRID_WIDTH);
    board_solution = create_empty_board(GRID_HEIGHT, GRID_WIDTH);

    generate_board(board, board_solution, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, num_of_hints);
    print_board(board, GRID_WIDTH, GRID_HEIGHT, BOX_WIDTH, BOX_HEIGHT);

    /*game begin*/
    while (TRUE) {
        has_won = is_game_won(board, GRID_HEIGHT, GRID_WIDTH);

        user_input = parse_command();

        if (has_won && user_input.command_chosen != restart_move && user_input.command_chosen != exit_game){
            printf(INVALID_COMMAND_ERROR);
            continue;
        }

        if (user_input.command_chosen == set_move) {
            /* check for right row,col position */
            if (set(board, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, user_input.params[0] - 1,
                    user_input.params[1] - 1, user_input.params[2]) >= 0) {
                print_board(board, GRID_WIDTH, GRID_HEIGHT, BOX_WIDTH, BOX_HEIGHT);
            }

        } else if (user_input.command_chosen == hint_move) {
            hint(board_solution, user_input.params[0] - 1, user_input.params[1] - 1);
        } else if (user_input.command_chosen == validate_move) {
            validate(board, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, board_solution);
        } else if (user_input.command_chosen == restart_move) {
            /* emptying the board */
            empty_board(board, GRID_HEIGHT, GRID_WIDTH);
            empty_board(board_solution, GRID_HEIGHT, GRID_WIDTH);

            if (get_cells_number_input(&num_of_hints) == 0) {
                printf("Error: not a number\n");
                for (i = 0; i < GRID_HEIGHT; i++)
                    free(board[i]);

                for (i = 0; i < GRID_HEIGHT; i++)
                    free(board_solution[i]);

                free(board);
                free(board_solution);
                printf(EXIT_MSG);
                return SUCCESS;
            }
            generate_board(board, board_solution, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, num_of_hints);
            print_board(board, GRID_WIDTH, GRID_HEIGHT, BOX_WIDTH, BOX_HEIGHT);


        } else if (user_input.command_chosen == exit_game) {
            for (i = 0; i < GRID_HEIGHT; i++)
                free(board[i]);

            for (i = 0; i < GRID_HEIGHT; i++)
                free(board_solution[i]);

            free(board);
            free(board_solution);
            printf(EXIT_MSG);
            return SUCCESS;
        }

        else {
            printf(INVALID_COMMAND_ERROR);
        }

    }

}