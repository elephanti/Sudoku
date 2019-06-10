#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include "solver.h"
#include "mainaux.h"

/**
 * Check whether a number is already used in a given row
 * @param grid The game board
 * @param grid_width The width of the board
 * @param row The row to search the number for
 * @param current_col The current col of the cell we want to place the number at
 * @param num The number to place
 * @return 1 = Not used, 0 = Used in row.
 */
int used_in_row(struct Cell **grid, int grid_width, int row, int current_col, int num) {
    int col;
    for (col = 0; col < grid_width; col++)
        if (current_col != col && grid[row][col].value == num)
            return TRUE;
    return FALSE;
}

/**
 * Check whether a number is already used in a given col
 * @param grid The game board
 * @param grid_height The height of the board
 * @param current_row The current row of the cell we want to place the number at
 * @param col The col to search the number for
 * @param num The number to place
 * @return 1 = Not used, 0 = Used in col.
 */
int used_in_col(struct Cell **grid, int grid_height, int current_row, int col, int num) {
    int row;
    for (row = 0; row < grid_height; row++)
        if (current_row != row && grid[row][col].value == num)
            return TRUE;
    return FALSE;
}

/**
 * Check whether a given number is already used in a given box
 * @param grid The game board
 * @param box_start_row The box's starting row
 * @param box_start_col The box's starting col
 * @param box_height The box height
 * @param box_width The box width
 * @param current_row The current row to place the num at
 * @param current_col The current col to place the num at
 * @param num The number to place
 * @return 1 = No used, 0 = Used in the box.
 */
int
used_in_box(struct Cell **grid, int box_start_row, int box_start_col, int box_height, int box_width, int current_row,
            int current_col, int num) {
    int row;
    int col;
    for (row = 0; row < box_height; row++)
        for (col = 0; col < box_width; col++)
            if (!(current_row == row && current_col == col) &&
                grid[row + box_start_row][col + box_start_col].value == num)
                return TRUE;
    return FALSE;
}

/**
 * Check whether it is valid to place a number in a given location
 * @param grid The game board
 * @param grid_height The board height
 * @param grid_width The board width
 * @param box_height The box height
 * @param box_width The box width
 * @param row The row to place the number at
 * @param col The column to place the number at
 * @param num The number to place
 * @return 1 = Valid, 0 = Invalid.
 */
int is_valid(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row, int col,
             int num) {
    if (num != UNASSIGNED)
        return !used_in_row(grid, grid_width, row, col, num) &&
               !used_in_col(grid, grid_height, row, col, num) &&
               !used_in_box(grid, row - row % box_height, col - col % box_width, box_height, box_width, row, col, num);
    return TRUE;
}

/**
 * Find valid values for a given cell
 * @param grid The game board
 * @param grid_height The board height
 * @param grid_width The board width
 * @param box_height the box height
 * @param box_width The box width
 * @param row The row of the cell
 * @param col The column of the cell
 * @param values The values array to fill with valid values
 * @param range Upper bound of the numbers range that is valid for the cell.
 * @return Number of valid values found
 */
int
find_valid_values(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row, int col,
                  int *values, int range) {
    int num;
    int counter = 0;
    int i = 0;
    for (num = 1; num <= range; num++) {
        /* For each number up to the range bound - check if its valid */
        if (is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, num)) {
            values[i] = num;
            i++;
            counter++;
        }
    }

    return counter;
}

/**
 * Check whether the cell is empty
 * @param grid The game board
 * @param row The row of the cell
 * @param col The column of the cell
 * @return 1 = Empty, 0 = Filled
 */
int is_empty(struct Cell **grid, int row, int col) {
    if (grid[row][col].value == UNASSIGNED)
        return TRUE;
    return FALSE;
}

/**
 * Given an array and an index, remove the number at the index from the array.
 * @param arr The array to remove the number from
 * @param index The index of the number to remove
 * @param arr_length The length of the array
 */
void delete_from_array(int *arr, int index, int arr_length) {
    int c;
    for (c = index; c < arr_length - 1; c++) {
        arr[c] = arr[c + 1];
    }
}

/**
 * Solve a board game grid recursively
 * @param grid The game board
 * @param grid_height The board height
 * @param grid_width The width of the board
 * @param box_height The box height
 * @param box_width The box width
 * @param row The row of the cell to start solving from
 * @param col The column of the cell to start solving from
 * @return 1 = Solved, 0 = No solution found
 */
int solve_grid_recursive(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row,
                         int col) {
    int num;
    int random_index;
    int num_of_values;
    if (row == grid_height)
        return TRUE;

    if (!is_empty(grid, row, col)) {
        /* Current cell is not empty - skip it and try the next one */
        if (col + 1 < grid_width) {
            /* If we can go further right - then go there and solve from there */
            return solve_grid_recursive(grid, grid_height, grid_width, box_height, box_width, row, col + 1);
        } else {
            /* End of the row - go to the next one and try to solve from there */
            return solve_grid_recursive(grid, grid_height, grid_width, box_height, box_width, row + 1, 0);
        }
    } else {
        /* Get all the values that are currently valid for the current cel */
        int *values = (int *) malloc(9 * sizeof(int));
        /*check if malloc has failed*/
        if (!values) {
            printf(FUNCTION_FAILED, "malloc");
            exit(0);
        }
        num_of_values = find_valid_values(grid, grid_height, grid_width, box_height, box_width, row, col, values,
                                          9);

        while (num_of_values != 0) {
            if (num_of_values == 1) {
                random_index = 0;

            } else {
                /* Randomly choose a valid number to try */
                random_index = rand() % num_of_values;

            }

            num = values[random_index];

            /* Check if num is valid value for the current cell */
            if (is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, num)) {
                /* Fill the cell with the proposed num */
                grid[row][col].value = num;

                if (col + 1 < grid_width) {
                    /* If we can go further right - then go there */
                    if (solve_grid_recursive(grid, grid_height, grid_width, box_height, box_width, row, col + 1)) {
                        /* Success! */
                        free(values);
                        return TRUE;
                    }
                } else {
                    /* End of the row - go to the next one */
                    if (solve_grid_recursive(grid, grid_height, grid_width, box_height, box_width, row + 1, 0)) {
                        /* Success! */
                        free(values);
                        return TRUE;
                    }
                }

                /* No solution found with current num as value in current cell - backtrack */
                grid[row][col].value = UNASSIGNED;
                /* Delete the number from possible values */
                delete_from_array(values, random_index, num_of_values);
                num_of_values--;
            }
        }

        /* No solution found for current board - return False (to trigger backtracking) */
        free(values);
        return FALSE;
    }
}



/**
 * Solve a board game grid recursively
 * @param grid The game board
 * @param grid_height The board height
 * @param grid_width The width of the board
 * @param box_height The box height
 * @param box_width The box width
 * @param row The row of the cell to start solving from
 * @param col The column of the cell to start solving from
 * @param flag 1 randomly 2 deterministic
 * @return 1 = Solved, 0 = No solution found
 */
int solve_grid_recursive_general(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row,
                         int col, int flag) {
    int num;
    int current_index;
    int num_of_values;
    if (row == grid_height)
        return TRUE;

    current_index = 0;
    if (!is_empty(grid, row, col)) {
        /* Current cell is not empty - skip it and try the next one */
        if (col + 1 < grid_width) {
            /* If we can go further right - then go there and solve from there */
            return solve_grid_recursive_general(grid, grid_height, grid_width, box_height, box_width, row, col + 1, flag);
        } else {
            /* End of the row - go to the next one and try to solve from there */
            return solve_grid_recursive_general(grid, grid_height, grid_width, box_height, box_width, row + 1, 0, flag);
        }
    } else {
        /* Get all the values that are currently valid for the current cel */
        int *values = (int *) malloc(9 * sizeof(int));
        /*check if malloc has failed*/
        if (!values) {
            printf(FUNCTION_FAILED, "malloc");
            exit(0);
        }
        num_of_values = find_valid_values(grid, grid_height, grid_width, box_height, box_width, row, col, values,
                                          9);

        while (num_of_values != 0) {
            if (num_of_values == 1) {
                if( flag == RANDOMLY){
                    current_index = 0;
                }
            } else {
                if(flag == RANDOMLY){
                    /* Randomly choose a valid number to try */
                    current_index = rand() % num_of_values;
                }
                

            }

            num = values[current_index];

            /* Check if num is valid value for the current cell */
            if (is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, num)) {
                /* Fill the cell with the proposed num */
                grid[row][col].value = num;

                if (col + 1 < grid_width) {
                    /* If we can go further right - then go there */
                    if (solve_grid_recursive_general(grid, grid_height, grid_width, box_height, box_width, row, col + 1, flag)) {
                        /* Success! */
                        free(values);
                        return TRUE;
                    }
                } else {
                    /* End of the row - go to the next one */
                    if (solve_grid_recursive_general(grid, grid_height, grid_width, box_height, box_width, row + 1, 0, flag)) {
                        /* Success! */
                        free(values);
                        return TRUE;
                    }
                }

                /* No solution found with current num as value in current cell - backtrack */
                grid[row][col].value = UNASSIGNED;
                if(flag == RANDOMLY){
                    /* Delete the number from possible values */
                    delete_from_array(values, current_index, num_of_values);
                    num_of_values--;
                }else{
                    current_index++;
                    num_of_values--;
                }
                
            }
        }

        /* No solution found for current board - return False (to trigger backtracking) */
        free(values);
        return FALSE;
    }
}




/**
 * Solve a grid (non-deterministically)
 * @param grid The game board
 * @param grid_height The height of the board
 * @param grid_width The width of the board
 * @param box_height The box height
 * @param box_width The box width
 * @return 1 = Board was solved, 0 = No solution found
 */
int solve_grid(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width) {
    /*return solve_grid_recursive(grid, grid_height, grid_width, box_height, box_width, 0, 0);*/
    return solve_grid_recursive_general(grid, grid_height, grid_width, box_height, box_width, 0, 0, 1);
}

/**
 * Solve the board deterministically
 * @param grid The game board
 * @param grid_height The board height
 * @param grid_width The width of the board
 * @param box_height The box height
 * @param box_width The box width
 * @param row The row of the cell to start solving from
 * @param col The column of the cell to start solving from*
 * @return 1 = Solved, 0 = No solution found.
 */
int solve_grid_recursive_deterministic(struct Cell **grid, int grid_height, int grid_width, int box_height,
                                       int box_width,
                                       int row,
                                       int col) {
    int i;
    if (row >= grid_height) {
        /* Went through the whole board and didnt solve the sudoku. */
        return TRUE;
    }
    /* Boundaries check */
    if (col >= grid_width) {
        return solve_grid_recursive_deterministic(grid, grid_height, grid_width, box_height, box_width, row + 1, 0);
    }

    /* Correct solution of a board */

    if (grid[row][col].is_const == TRUE || grid[row][col].value != UNASSIGNED) {
        /* We are within a legitimate cell. */
        return solve_grid_recursive_deterministic(grid, grid_height, grid_width, box_height, box_width, row, col + 1);
    }

    /*maybe width?*/
    for (i = 1; i <= GRID_HEIGHT; i++) {
        if (is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, i)) {

            grid[row][col].value = i;

            if (solve_grid_recursive_deterministic(grid, grid_height, grid_width, box_height, box_width, row,
                                                   col + 1)) {
                return TRUE;
            } else {
                grid[row][col].value = UNASSIGNED;
            }
        }

    }
    return FALSE;
}


/**
 * Generate a new game board
 * @param grid The pointer to the board to fill
 * @param solution The pointer to the solution to fill
 * @param grid_height The height of the board
 * @param grid_width The width of the board
 * @param box_height The box height
 * @param box_width The box width
 * @param num_of_hints the number of hints to remain on the board
 * @return 0 = Success
 */
int generate_board(struct Cell **grid, struct Cell **solution, int grid_height, int grid_width, int box_height,
                   int box_width, int num_of_hints) {
    int current_hints = 0;
    int row;
    int col;
    int i;
    int j;

    /* Reset the grid - fill the board with empty values */
    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            grid[i][j].value = UNASSIGNED;
            grid[i][j].is_const = FALSE;
        }
    }

    /* Populate the board */
    solve_grid(grid, grid_height, grid_width, box_height, box_width);

    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            solution[i][j].value = grid[i][j].value;
            solution[i][j].is_const = FALSE;
        }
    }

    /* Remove cells until only num_of_hints hints are remained */
    while (current_hints != num_of_hints) {
        col = rand() % grid_height;
        row = rand() % grid_width;

        if (grid[row][col].is_const == FALSE) {
            grid[row][col].is_const = TRUE;
            solution[row][col].is_const = TRUE;
            current_hints++;
        }
    }

    /* Remove non fixed cells */
    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            if (grid[i][j].is_const == FALSE)
                grid[i][j].value = UNASSIGNED;
        }
    }

    return 0;
}

/**
 * Check if a game was won
 * @param grid The game board
 * @param grid_height The board height
 * @param grid_width The board width
 * @return 1 = Game was won, 0 - Game is not won.
 */
int is_game_won(struct Cell **grid, int grid_height, int grid_width) {
    int i;
    int j;
    for (i = 0; i < grid_height; i++) {
        for (j = 0; j < grid_width; j++) {
            if (grid[i][j].value == UNASSIGNED)
                return FALSE;
        }
    }

    return TRUE;
}



int test() {
    int i;
    struct Cell **grid = create_empty_board(GRID_HEIGHT, GRID_WIDTH);
    struct Cell **solution = create_empty_board(GRID_HEIGHT, GRID_WIDTH);

    generate_board(grid, solution, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, 0);
    printf("Original Solution:\n");
    print_board(solution, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH);
    printf("Board to solve:\n");
    print_board(grid, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH);

    if (solve_grid_recursive_deterministic(grid, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, 0, 0) == TRUE) {
        printf("Found solution:\n");
        print_board(grid, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH);
    } else
        printf("No solution exists");

    for (i = 0; i < GRID_HEIGHT; i++)
        free(grid[i]);

    free(grid);
    free(solution);

    return 0;

}

int test2() {
    int i;
    struct Cell **grid = create_empty_board(GRID_HEIGHT, GRID_WIDTH);
    struct Cell **solution = create_empty_board(GRID_HEIGHT, GRID_WIDTH);

    generate_board(grid, solution, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, 76);
    printf("Original Solution:\n");
    print_board(solution, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH);
    printf("Board to solve:\n");
    print_board(grid, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH);

    if (solve_grid_recursive_deterministic(grid, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH, 0, 0) == TRUE) {
        printf("Found solution:\n");
        print_board(grid, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH);
    } else
        printf("No solution exists");

    for (i = 0; i < GRID_HEIGHT; i++)
        free(grid[i]);

    free(grid);
    free(solution);

    return 0;

}
