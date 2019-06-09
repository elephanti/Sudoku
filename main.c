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
        seed = DEFAULT_SEED;
    }

    else {
        seed = atoi(argv[1]);
    }

    /* Set the seed for the randomization */
    srand(seed);

    /* Get the number of hints to remain on the board */
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

    /* Game begins */
    while (TRUE) {
        /* Check if game was won in previous turn */
        has_won = is_game_won(board, GRID_HEIGHT, GRID_WIDTH);

        /* Parse the current command */
        user_input = parse_command();

        /* If game was won, valid commands are restart and exit only. */
        if (has_won && user_input.command_chosen != restart_move && user_input.command_chosen != exit_game){
            printf(INVALID_COMMAND_ERROR);
            continue;
        }

        if (user_input.command_chosen == set_move) {
            /* Perform set command */
            set(board, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, user_input.params[0] - 1,
                    user_input.params[1] - 1, user_input.params[2]);
        } else if (user_input.command_chosen == hint_move) {
            /* Perform hint command */
            hint(board_solution, user_input.params[0] - 1, user_input.params[1] - 1);
        } else if (user_input.command_chosen == validate_move) {
            /* Perform validate comment */
            validate(board, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, board_solution);
        } else if (user_input.command_chosen == restart_move) {
            /* Perform restart command */
            /* Empty the board and the solution */
            empty_board(board, GRID_HEIGHT, GRID_WIDTH);
            empty_board(board_solution, GRID_HEIGHT, GRID_WIDTH);

            /* Get new number of hints to remain on the board */
            if (get_cells_number_input(&num_of_hints) == 0) {
                printf("Error: not a number\n");

                /* Invalid input - free the board and solution */
                for (i = 0; i < GRID_HEIGHT; i++)
                    free(board[i]);

                for (i = 0; i < GRID_HEIGHT; i++)
                    free(board_solution[i]);

                free(board);
                free(board_solution);

                /* Exit */
                printf(EXIT_MSG);
                return SUCCESS;
            }

            /* Generate new boards */
            generate_board(board, board_solution, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, num_of_hints);
            print_board(board, GRID_WIDTH, GRID_HEIGHT, BOX_WIDTH, BOX_HEIGHT);


        } else if (user_input.command_chosen == exit_game) {
            /* Perform exit command*/
            /* Free boards and exit */
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
            /* Invalid command */
            printf(INVALID_COMMAND_ERROR);
        }

    }

}