#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdlib.h>
#include "mainaux.h"

/**
 * Print the current board to the user
 * @param grid The game board
 * @param grid_height The height of game board
 * @param grid_width The width of the game board
 * @param box_height The height of a sudoku box
 * @param box_width The width of a sudoku box
 */
void print_board(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width) {
    int i, j, k, line_length, boxes_amount;
    boxes_amount = grid_width / box_width;

    /* The formula for lines given by Moshe. */
    line_length = boxes_amount * (CHARACTERS_IN_CELL * box_width + 2) + 1;

    for (i = 0; i < grid_height; i++) {
        /* Printing the horizontal lines */

        if (i % box_height == 0) {
            for (k = 0; k < line_length; k++) {
                printf("-");
            }
            printf("\n");
        }
        for (j = 0; j < grid_width; j++) {
            if (j == 0) {
                /* the box frame */
                printf("| ");
            } else if (j % box_width == 0) {
                printf("| ");
            }

            if (grid[i][j].value == UNASSIGNED)
                printf(EMPTY_CELL);

            else if (grid[i][j].is_const == FALSE) {
                printf(NORMAL_CELL, grid[i][j].value);
            } else {
                /* Its is a constant value */
                printf(CONST_CELL, grid[i][j].value);
            }


            if (j == grid_width - 1) {
                /* The box frame */
                printf("|\n");
            }

        }
    }

    /* One last horizontal line. */
    for (k = 0; k < line_length; k++) {
        printf("-");
    }
    printf("\n");
}

/**
 * Check if an input is in valid range
 * @param num The input
 * @param max_num_in_range The upper bound of the range
 * @return 1 = Valid, 0 = Invalid.
 */
int is_valid_input(int num, int max_num_in_range) {
    return num >= 0 && num <= max_num_in_range;
}

/**
 * Print validation failed message.
 */
void print_validation_failed() {
    printf(VALIDATION_FAILED);
}

/**
 * Print validation passed message.
 */
void print_validation_passed() {
    printf(VALIDATION_PASSED);
}

/**
 * Print invalid value error
 */
void print_invalid_value() {
    printf(INVALID_VALUE_ERROR);
}

/**
 * Print fixed cell error
 */
void print_fixed_cell_error() {
    printf(CELL_IS_FIXED_ERROR);
}

/**
 * Print winning message
 */
void print_winning_message() {
    printf(WIN_MSG);
}

/**
 * Print hint message
 * @param hint_value The hint value to print
 */
void print_hint_message(int hint_value) {
    printf(HINT_MSG, hint_value);
}

/**
 * Copy a board
 * @param source_grid The board to copy from
 * @param destination_grid The board to copy to
 * @param grid_height The height of the board
 * @param grid_width The width of the board
 */
void copy_board(struct Cell **source_grid, struct Cell **destination_grid, int grid_height, int grid_width) {
    int i;
    int j;
    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            destination_grid[i][j].value = source_grid[i][j].value;
            destination_grid[i][j].is_const = source_grid[i][j].is_const;
        }
    }
}

/**
 * Create an empty board
 * @param grid_height The board height
 * @param grid_width The board width
 * @return
 */
struct Cell **create_empty_board(int grid_height, int grid_width) {
    struct Cell **grid = (struct Cell **) malloc(grid_height * grid_width * sizeof(struct Cell));
    int i;
    int j;

    /*check if malloc failed*/
    if(!grid){
        printf(FUNCTION_FAILED, "malloc");
        exit(0);
    }
    for (i = 0; i < grid_height; i++){
        grid[i] = (struct Cell *) malloc(grid_width * sizeof(struct Cell));
        /*check if malloc failed*/
        if(!grid[i]){
            printf(FUNCTION_FAILED, "malloc");
            exit(0);
        }
        
    }
        
    /* Initiate the board */
    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            struct Cell cell;
            cell.value = UNASSIGNED;
            cell.is_const = FALSE;
            grid[i][j] = cell;
        }
    }

    return grid;
}

/**
 * Empty a given board
 * @param board_to_empty The board to empty
 * @param grid_height The board height
 * @param grid_width The board width
 */
void empty_board(struct Cell **board_to_empty, int grid_height, int grid_width) {
    int i, j;
    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            board_to_empty[i][j].value = UNASSIGNED;
            board_to_empty[i][j].is_const = FALSE;
        }
    }
}

/**
 * Get the number of hints to remain on the board
 * @param num_of_hints The pointer to the variable that holds the number of hints
 * @return 1 = Success, 0 = Error.
 */
int get_cells_number_input(int* num_of_hints){
    /* Scanning user input */
    int result;
    printf(NUMBER_OF_CELLS_TO_FILL_MSG);
    result = scanf("%d%*c", num_of_hints);
    if(result==EOF){
        printf(EXIT_MSG);
        exit(0);
    }
    if (result == 0)
        return result;

    while (*num_of_hints < 0 || *num_of_hints > 80) {
        printf(INVALID_NUMBER_OF_CELLS_TO_FILL);
        printf(NUMBER_OF_CELLS_TO_FILL_MSG);
        result = scanf("%d%*c", num_of_hints);
        if (result == 0)
            return result;
    }

    return 1;
}