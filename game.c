//
// Created by avital on 28/05/2019.
//

#include "game.h"
#include "mainaux.h"
#include "solver.h"

int set(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
        int row, int col, int value){
    if (!is_valid_input(value, GRID_HEIGHT)) {
        print_invalid_value();
        return -1;
    }

    if (grid[row][col].is_const == TRUE) {
        print_fixed_cell_error();
        return -1;
    }

    if (!is_valid(grid, grid_height, grid_width, box_height, box_width, row, col, value))
    {
        print_invalid_value();
        return -1;
    }

    grid[row][col].value = value;
    print_board(grid, grid_height, grid_width, box_height, box_width);

    if (is_game_won(grid, grid_height, grid_width)) {
        print_winning_message();
        return 1;
    }

    return 0;

}


int hint(struct Cell **solution, int row, int col) {
    print_hint_message(solution[row][col].value);

    return 0;
}

int validate(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
             int row, int col, int value) {
    
}