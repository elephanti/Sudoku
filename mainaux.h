#ifndef SUDOKU_MAIN_AUX_H
#define SUDOKU_MAIN_AUX_H

#define UNASSIGNED 0
#define GRID_HEIGHT 9
#define GRID_WIDTH 9
#define BOX_HEIGHT 3
#define BOX_WIDTH 3
#define CHARACTERS_IN_CELL 3

#define TRUE 1
#define FALSE 0

#define EMPTY_CELL "   "
#define NORMAL_CELL " %d "
#define CONST_CELL ".%d "
#define CELL_IS_FIXED_ERROR "Error: cell is fixed\n"
#define INVALID_VALUE_ERROR "Error: value is invalid\n"
#define WIN_MSG "Puzzle solved successfully\n"
#define HINT_MSG "Hint: set cell to %d\n"
#define VALIDATION_FAILED "Validation failed: board is unsolvable\n"
#define VALIDATION_PASSED "Validation passed: board is solvable\n"

struct Cell {
    int value;
    int is_const;
} cell;

void print_board(struct Cell** grid, int grid_width, int grid_height,int box_width, int box_height);
int is_valid_input(int num, int max_num_in_range);
void print_invalid_value();
void print_fixed_cell_error();
void print_winning_message();
void print_hint_message(int hint_value);
void print_validation_failed();
void print_validation_passed();
struct Cell** create_empty_board(int grid_height, int grid_width);
void copy_board(struct Cell **grid1, struct Cell **grid2, int grid_height, int grid_width);




#endif
