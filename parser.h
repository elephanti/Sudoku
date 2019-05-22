//
// Created by yair on 22/05/2019.
//



#define TRUE 1
#define FALSE 0
#define MAX_COMMAND_LENGTH 1024

typedef enum Type{invalid_type,set,hint,validate,restart,exit_game}command_type;


typedef struct comm{
    command_type command_chosen;
    int params[3] ;
    int param_amount;
}command;
int equals(char * str1,char * str2);
command parse_command();


