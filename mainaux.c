#include <stdio.h>
#include <malloc.h>
#include "mainaux.h"


void print_board(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width) {
    int i, j, k, line_length, boxes_amount;
    boxes_amount = grid_width / box_width;

    /* The formule for lines given by moshe. */
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

int is_valid_input(int num, int max_num_in_range) {
    return num >= 0 && num <= max_num_in_range;
}

void print_validation_failed() {
    printf(VALIDATION_FAILED);
}

void print_validation_passed() {
    printf(VALIDATION_PASSED);
}

void print_invalid_value() {
    printf(INVALID_VALUE_ERROR);
}

void print_fixed_cell_error() {
    printf(CELL_IS_FIXED_ERROR);
}

void print_winning_message() {
    printf(WIN_MSG);
}

void print_hint_message(int hint_value) {
    printf(HINT_MSG, hint_value);
}

void copy_board(struct Cell **grid1, struct Cell **grid2, int grid_height, int grid_width) {
    int i;
    int j;
    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            grid2[i][j].value = grid1[i][j].value;
            grid2[i][j].is_const = grid1[i][j].is_const;
        }
    }
}

struct Cell **create_empty_board(int grid_height, int grid_width) {
    struct Cell **grid = (struct Cell **) malloc(grid_height * grid_width * sizeof(struct Cell));
    int i;
    int j;

    /*check if malloc failed*/
    if(!grid){
        printf("Error: malloc has failed\n");
        exit(0);
    }
    for (i = 0; i < grid_height; i++){
        grid[i] = (struct Cell *) malloc(grid_width * sizeof(struct Cell));
        /*check if malloc failed*/
        if(!grid[i]){
            printf("Error: malloc has failed\n");
            exit(0);
        }
        
    }
        

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

void empty_board(struct Cell **board_to_empty, int grid_height, int grid_width) {
    int i, j;
    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            board_to_empty[i][j].value = UNASSIGNED;
            board_to_empty[i][j].is_const = FALSE;
        }
    }
}

void get_cells_number_input(int* num_of_hints){
    /* Scanning user input */
    printf(NUMBER_OF_CELLS_TO_FILL_MSG);
    scanf("%d%*c", num_of_hints);

    while (*num_of_hints < 0 || *num_of_hints > 80) {
        printf(INVALID_NUMBER_OF_CELLS_TO_FILL);
        printf(NUMBER_OF_CELLS_TO_FILL_MSG);
        scanf("%d%*c", num_of_hints);
    }
}