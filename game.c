#include "game.h"
#include "mainaux.h"
#include "solver.h"

#include <stdlib.h>
#include <stdio.h>

int set(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
        int col, int row, int value) {
    if (!is_valid_input(value, GRID_HEIGHT)) {
        print_invalid_value();
        return -1;
    }

    if (grid[row][col].is_const == TRUE) {
        print_fixed_cell_error();
        return -1;
    }

    if (!is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, value)) {
        print_invalid_value();
        return -1;
    }

    grid[row][col].value = value;

    if (is_game_won(grid, grid_height, grid_width)) {
        print_winning_message();
        return 1;
    }

    return 0;

}


int hint(struct Cell **solution, int col, int row) {
    print_hint_message(solution[row][col].value);

    return 0;
}

int validate(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
             struct Cell **current_solution) {
    int i;
    struct Cell **new_solution = create_empty_board(GRID_HEIGHT, GRID_WIDTH);
    copy_board(grid, new_solution, grid_height, grid_width);

    /*if board is solvable - update the solution*/

    if (solve_grid_recursive_deterministic(new_solution, grid_height, grid_width, box_height, box_width, 0, 0) ==
        TRUE) {
        /*free memory allocation for previous solution */
        for (i = 0; i < grid_height; i++) {
            free(current_solution[i]);
        }
        free(current_solution);
        current_solution = new_solution;
        print_validation_passed();
        return TRUE;

    } else {
        print_validation_failed();
        return FALSE;
    }

}