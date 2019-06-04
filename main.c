/*created by Yair on 3.6.19*/
#include "game.h"
#include "mainaux.h"
#include "solver.h"
#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#define WRONG_VALUE -1
#define SUCCESS 1

int main(int argc, char *argv[]){
    struct Cell **board, **board_solution;
    int num_of_hints;
    command user_input;
    int valid_command;
    /*SCAN SEED HERE*/
    /*scanning user input*/
    printf("Please enter the number of cells to fill [0-80]:\n");
    scanf("%d%*c",&num_of_hints);
    
    while(num_of_hints < 0 || num_of_hints > 80){
        printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
        printf("Please enter the number of cells to fill [0-80]:\n");
        scanf("%d%*c",&num_of_hints);
    }

    /*initalizing the game*/
    board = create_empty_board(GRID_HEIGHT,GRID_WIDTH);
    board_solution = create_empty_board(GRID_HEIGHT,GRID_WIDTH);

    generate_board(board,board_solution,GRID_HEIGHT,GRID_WIDTH,BOX_HEIGHT,BOX_WIDTH,num_of_hints);
    valid_command=TRUE;

    /*game begin*/
    while(!is_game_won(board,GRID_HEIGHT,GRID_WIDTH)){

        if(valid_command){
            /*print the baord only if the last command was a valid one.*/
            print_board(board,GRID_WIDTH,GRID_HEIGHT,BOX_WIDTH,BOX_HEIGHT);
        }
        
        user_input = parse_command();
        /*acting accordingly to command*/
        if(user_input.command_chosen==invalid_type){
            printf("Error: invalid command\n");
        }else if(user_input.command_chosen==set_move){
            //check for right row,col position
            if(set(board, GRID_HEIGHT, GRID_WIDTH, BOX_HEIGHT, BOX_WIDTH
                    ,user_input.params[0]-1, user_input.params[1]-1, user_input.params[2])<0){

                valid_command=FALSE;
            }else{
                valid_command=TRUE;
                //keep checking if keeping the game or the dude won
            }

        }else if(user_input.command_chosen==hint_move){
            hint(board_solution,user_input.params[0]-1,user_input.params[1]);
        }else if(user_input.command_chosen==validate_move){
            validate(board,GRID_HEIGHT,GRID_WIDTH,BOX_HEIGHT,BOX_WIDTH,user_input.params[0]-1,user_input.params[1],board_solution);
        }else if(user_input.command_chosen==restart_move){
            //emptying the board
            empty_board(board,GRID_HEIGHT,GRID_WIDTH);
            empty_board(board_solution,GRID_HEIGHT,GRID_WIDTH);

            /*scanning user input*/
            printf("Please enter the number of cells to fill [0-80]:\n");
            scanf("%d%*c",&num_of_hints);
    
            while(num_of_hints < 0 || num_of_hints > 80){
                printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
                printf("Please enter the number of cells to fill [0-80]:\n");
                scanf("%d%*c",&num_of_hints);
            }
            generate_board(board,board_solution,GRID_HEIGHT,GRID_WIDTH,BOX_HEIGHT,BOX_WIDTH,num_of_hints);
            
        }else if(user_input.command_chosen==exit_game){
            free(board);
            free(board_solution);
            printf("Exiting...\n");
            return SUCCESS;
        }
    }




}