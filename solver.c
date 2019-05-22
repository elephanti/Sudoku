//
// Created by avital on 22/05/2019.
//

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include "solver.h"

struct Cell {
    int value;
    int is_const;
} cell;


/* Returns a boolean which indicates whether an assigned entry
   in the specified row matches the given number. */
int used_in_row(struct Cell **grid, int grid_width, int row, int num) {
    for (int col = 0; col < grid_width; col++)
        if (grid[row][col].value == num)
            return TRUE;
    return FALSE;
}

/* Returns a boolean which indicates whether an assigned entry
   in the specified column matches the given number. */
int used_in_col(struct Cell **grid, int grid_height, int col, int num) {
    for (int row = 0; row < grid_height; row++)
        if (grid[row][col].value == num)
            return TRUE;
    return FALSE;
}

/* Returns a boolean which indicates whether an assigned entry
   within the specified 3x3 box matches the given number. */
int used_in_box(struct Cell **grid, int box_start_row, int box_start_col, int box_height, int box_width, int num) {
    for (int row = 0; row < box_height; row++)
        for (int col = 0; col < box_width; col++)
            if (grid[row + box_start_row][col + box_start_col].value == num)
                return TRUE;
    return FALSE;
}

/* Returns a boolean which indicates whether it will be legal to assign
   num to the given row,col location. */
int is_valid(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row, int col,
             int num) {
    return !used_in_row(grid, grid_width, row, num) &&
           !used_in_col(grid, grid_height, col, num) &&
           !used_in_box(grid, row - row % box_height, col - col % box_width, box_height, box_width, num) &&
           grid[row][col].value == UNASSIGNED;
}

int
find_valid_values(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row, int col,
                  int *values, int range) {
    int num;
    int counter = 0;
    for (num = 1; num <= range; num++) {
        if (is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, num)) {
            values[0] = num;
            values++;
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
    for (int c = index - 1; c < arr_length - 1; c++)
        arr[c] = arr[c + 1];
}

int solve_grid_recursive(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width, int row,
                         int col) {
    int num;

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

    /* Get all the values that are currently valid for the current cel */
    int *values = (int *) malloc(9 * sizeof(int));
    int num_of_values = find_valid_values(grid, grid_height, grid_width, box_height, box_width, row, col, values, 9);

    while (num_of_values != 0) {
        /* Randomly choose a valid number to try */
        int random_index = rand() % num_of_values;
        num = values[random_index];

        // Check if num is valid value for the current cell
        if (is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, num)) {
            // Fill the cell with the proposed num
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

int solve_grid(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width) {
    return solve_grid_recursive(grid, grid_height, grid_width, box_height, box_width, 0, 0);
}

/* A utility function to print grid  */
void print_grid(struct Cell **grid, int grid_height, int grid_width) {
    for (int row = 0; row < grid_height; row++) {
        for (int col = 0; col < grid_width; col++)
            printf("%2d", grid[row][col].value);
        printf("\n");
    }
}


int test() {
    // 0 means unassigned cells
    int int_grid[GRID_HEIGHT][GRID_WIDTH] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                                             {5, 2, 0, 0, 0, 0, 0, 0, 0},
                                             {0, 8, 7, 0, 0, 0, 0, 3, 1},
                                             {0, 0, 3, 0, 1, 0, 0, 8, 0},
                                             {9, 0, 0, 8, 6, 3, 0, 0, 5},
                                             {0, 5, 0, 0, 9, 0, 6, 0, 0},
                                             {1, 3, 0, 0, 0, 0, 2, 5, 0},
                                             {0, 0, 0, 0, 0, 0, 0, 7, 4},
                                             {0, 0, 5, 2, 0, 6, 3, 0, 0}};

    struct Cell **grid = (struct Cell **) malloc(GRID_HEIGHT * GRID_WIDTH * sizeof(struct Cell));

    for (int i = 0; i < GRID_HEIGHT; i++)
        grid[i] = (struct Cell *) malloc(GRID_WIDTH * sizeof(struct Cell));

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            struct Cell cell;
            cell.value = 0; //int_grid[i][j];
            cell.is_const = FALSE;
            grid[i][j] = cell;
        }
    }

    if (solve_grid(grid, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH) == TRUE)
        print_grid(grid, GRID_HEIGHT, GRID_WIDTH);
    else
        printf("No solution exists");

    for (int i = 0; i < GRID_HEIGHT; i++)
        free(grid[i]);

    free(grid);

    return 0;

}

int main() {
    srand(time(NULL));
    test();
}