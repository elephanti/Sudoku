#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include "solver.h"
#include "mainaux.h"

int used_in_row(struct Cell **grid, int grid_width, int row, int current_col, int num) {
    int col;
    for (col = 0; col < grid_width; col++)
        if (current_col != col && grid[row][col].value == num)
            return TRUE;
    return FALSE;
}

/* Returns a boolean which indicates whether an assigned entry
   in the specified column matches the given number. */
int used_in_col(struct Cell **grid, int grid_height, int current_row, int col, int num) {
    int row;
    for (row = 0; row < grid_height; row++)
        if (current_row != row && grid[row][col].value == num)
            return TRUE;
    return FALSE;
}

/* Returns a boolean which indicates whether an assigned entry
   within the specified 3x3 box matches the given number. */
int used_in_box(struct Cell **grid, int box_start_row, int box_start_col, int box_height, int box_width, int current_row, int current_col, int num) {
    int row;
    int col;
    for (row = 0; row < box_height; row++)
        for (col = 0; col < box_width; col++)
            if (!(current_row == row && current_col == col) && grid[row + box_start_row][col + box_start_col].value == num)
                return TRUE;
    return FALSE;
}

/* Returns a boolean which indicates whether it will be legal to assign
   num to the given row,col location. */
int is_valid(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row, int col,
             int num) {
    if (num != UNASSIGNED)
        return !used_in_row(grid, grid_width, row, col, num) &&
               !used_in_col(grid, grid_height, row, col, num) &&
               !used_in_box(grid, row - row % box_height, col - col % box_width, box_height, box_width, row, col, num);
    return TRUE;
}

int
find_valid_values(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row, int col,
                  int *values, int range) {
    int num;
    int counter = 0;
    int i=0;
    for (num = 1; num <= range; num++) {
        if (is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, num)) {
            values[i] = num;
            i++;
            counter++;
        }
    }

    return counter;
}

int is_empty(struct Cell **grid, int row, int col) {
    if (grid[row][col].value == UNASSIGNED)
        return TRUE;
    return FALSE;
}

void delete_from_array(int *arr, int index, int arr_length) {
    int c;
    for (c = index; c < arr_length - 1; c++) {
        arr[c] = arr[c + 1];
    }
}

int solve_grid_recursive(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row,
                         int col) {
    int num;
    int random_index;
    int num_of_values;
<<<<<<< HEAD
=======

>>>>>>> 56e8b8ce0362d90df0ca8bc7d0c060f86feac0cc
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
    }

    else {
        /* Get all the values that are currently valid for the current cel */
        int *values = (int *) malloc(9 * sizeof(int));
        /*check if malloc has failed*/
        if(!values){
            printf("Error: malloc has failed\n");
            exit(0);
        }
        num_of_values = find_valid_values(grid, grid_height, grid_width, box_height, box_width, row, col, values,
                                              9);

        while (num_of_values != 0) {
            if (num_of_values == 1) {
                random_index = 0;

            }
            else {
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
                        return TRUE;
                    }
                } else {
                    /* End of the row - go to the next one */
                    if (solve_grid_recursive(grid, grid_height, grid_width, box_height, box_width, row + 1, 0)) {
                        /* Success! */
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
        /* TODO: Free values. Need to figure out how cause it looks like it is being freed somehow */
        return FALSE;
    }
}

int solve_grid(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width) {
    return solve_grid_recursive(grid, grid_height, grid_width, box_height, box_width, 0, 0);
}


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
    for(i=1;i<=GRID_HEIGHT; i++){
        if(is_valid(grid,grid_height,grid_width,box_height,box_width,row,col,i)){

        grid[row][col].value=i;
        
            if(solve_grid_recursive_deterministic(grid, grid_height, grid_width, box_height, box_width, row, col + 1)){
                return TRUE;
            }
            else{
                grid[row][col].value=UNASSIGNED;
            }
        }
       
    }
    return FALSE;
}


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
    }
    else
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
    }
    else
        printf("No solution exists");

    for (i = 0; i < GRID_HEIGHT; i++)
        free(grid[i]);

    free(grid);
    free(solution);

    return 0;

}
/*
int main() {
    srand(time(NULL));
    test();
}*/