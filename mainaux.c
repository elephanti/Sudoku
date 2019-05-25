#include <stdio.h>
#include "mainaux.h"


void print_board(struct Cell** grid,int grid_width, int grid_height,int box_width, int box_height)
{
    int i,j,k, line_length,boxes_amount;
    boxes_amount=grid_width/box_width;
    line_length=boxes_amount*(CHARACTERS_IN_CELL*box_width+2)+1;//the ofrmula for lines given by moshe.
    for(i=0;i<grid_height;i++)
    {
        if(i % box_height==0)//printing the horizontal lines
        {
            for(k=0;k<line_length;k++)
            {
                printf("-");
            }
            printf("\n");
        }
        for(j=0;j<grid_width;j++)
        {
            if(j==0)//the box frame
            {
                printf("| ");
            }
            else if(j%box_width==0)
            {
                printf("| ");
            }

            if(grid[i][j].value==UNASSIGNED)
                printf("   ");
            else if(grid[i][j].is_const==FALSE)
            {
                printf(" %d ",grid[i][j].value);
            }
            else//its is a constant value
            {
                printf(".%d ",grid[i][j].value);
            }
            

            if(j==grid_width-1)//the box frame
            {
                printf("|\n");
            }

        }
    }
    //one last horizontal line.
     for(k=0;k<line_length;k++)
    {
        printf("-");
    }
        printf("\n");
}