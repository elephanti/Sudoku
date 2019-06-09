#include "game.h"
#include "mainaux.h"
#include "solver.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Perform set command. Set a value on a given cell.
 * @param grid The game board
 * @param grid_height The height of game board
 * @param grid_width The width of the game board
 * @param box_height The height of a sudoku box
 * @param box_width The width of a sudoku box
 * @param col The column of the cell to set
 * @param row The width of the cell to set
 * @param value The value to set to the cell
 * @return 1 = Game was won, 0 = Set was successful, -1 = Error.
 */
int set(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
        int col, int row, int value) {
    /* Validate the input */
    if (!is_valid_input(value, GRID_HEIGHT)) {
        print_invalid_value();
        return -1;
    }

    /* Validate the cell is not fixed */
    if (grid[row][col].is_const == TRUE) {
        print_fixed_cell_error();
        return -1;
    }

    /* Check that the input valid for the given cell */
    if (!is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, value)) {
        print_invalid_value();
        return -1;
    }

    /* Set the cell */
    grid[row][col].value = value;
    print_board(grid, GRID_WIDTH, GRID_HEIGHT, BOX_WIDTH, BOX_HEIGHT);

    /* Check if the game was won */
    if (is_game_won(grid, grid_height, grid_width)) {
        print_winning_message();
        return 1;
    }

    return 0;

}

/**
 * Perform a hint command. Give the player a hint (regardless of the current board state.
 * @param solution The stored board solution
 * @param col The column of the hinted cell
 * @param row The row of the hinted cell
 * @return 0 = Success.
 */
int hint(struct Cell **solution, int col, int row) {
    print_hint_message(solution[row][col].value);

    return 0;
}

/**
 * Perform validate command. Validate the current board and update the newly found solution.
 * If not solution exists - notify the player.
 * @param grid The game board
 * @param grid_height The height of game board
 * @param grid_width The width of the game board
 * @param box_height The height of a sudoku box
 * @param box_width The width of a sudoku box
 * @param current_solution The last game solution
 * @return 1 = Validation successful, 0 = No solution found.
 */
int validate(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
             struct Cell **current_solution) {
    int i;
    /* Create a temporary board for storing the new solution */
    struct Cell **new_solution = create_empty_board(GRID_HEIGHT, GRID_WIDTH);
    copy_board(grid, new_solution, grid_height, grid_width);

    /* If board is solvable - update the solution */

    if (solve_grid_recursive_deterministic(new_solution, grid_height, grid_width, box_height, box_width, 0, 0) ==
        TRUE) {
        /* Copy the found solution to the current solution */
        copy_board(new_solution, current_solution, grid_height, grid_width);

        /* Free memory allocation for previous solution */
        for (i = 0; i < grid_height; i++) {
            free(new_solution[i]);
        }
        free(new_solution);

        print_validation_passed();
        return TRUE;

    } else {
        /* No solution for the current board */
        /* Free memory allocation for previous solution */
        for (i = 0; i < grid_height; i++) {
            free(new_solution[i]);
        }
        free(new_solution);

        print_validation_failed();
        return FALSE;
    }

}