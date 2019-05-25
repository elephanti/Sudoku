#define UNASSIGNED 0
#define GRID_HEIGHT 9
#define GRID_WIDTH 9
#define BOX_HEIGHT 3
#define BOX_WIDTH 3
#define CHARACTERS_IN_CELL 3
#define TRUE 1
#define FALSE 0
struct Cell {
    int value;
    int is_const;
} cell;
void print_board(struct Cell** grid,int grid_width, int grid_height,int box_width, int box_height);