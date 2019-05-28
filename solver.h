//
// Created by avital on 22/05/2019.
//

#include "mainaux.h"

#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

int is_valid(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
             int row, int col, int num);

int generate_board(struct Cell **grid, struct Cell **solution, int grid_height, int grid_width, int box_height,
                   int box_width, int num_of_hints);

int solve_grid_recursive_deterministic(struct Cell **grid, int grid_height, int grid_width, int box_height,
                                       int box_width,
                                       int row,
                                       int col);

int is_game_won(struct Cell **grid, int grid_height, int grid_width);


#endif
