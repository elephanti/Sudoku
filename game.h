#ifndef NIM_GAME_H
#define NIM_GAME_H
#include "mainaux.h"

int validate(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
             struct Cell **current_solution);
int hint(struct Cell **solution, int row, int col) ;
int set(struct Cell **grid, int grid_height, int grid_width, int box_height, int box_width,
        int row, int col, int value);


#endif
