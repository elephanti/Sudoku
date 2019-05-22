//
// Created by yair on 22/05/2019.
//

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"


/*checking if*/
int equals(char * str1,char * str2)
{
    int i=0;
    while(str1[i]!=EOF && str1[i]!='\0' && str1[i]!='\n')
    { 
        if(str1[i]!=str2[i])
            return FALSE;
        i++;
    }
    return TRUE;
}


/*a command that recieves an input and returns a command struct
containing the parsed command from the user.*/
command parse_command()
{
    char user_input [MAX_COMMAND_LENGTH];
    char *token;
    command recieved_command;
    int param_amount;

    fgets(user_input,MAX_COMMAND_LENGTH,stdin);//user input as a whole row.
    
    token=strtok(user_input," ");
    /*parsing the command type.*/
    if(equals(token,"set"))
    {
        recieved_command.command_chosen=set;
        param_amount=3;
    }
    else if(equals(token,"hint"))
    {
        recieved_command.command_chosen=hint;
        param_amount=2;
    }
    else if(equals(token,"validate"))
    {
        recieved_command.command_chosen=validate;
        return recieved_command;
    }
    else if(equals(token,"restart"))
    {
        recieved_command.command_chosen=restart;
    }
    else if(equals(token,"exit"))
    {
        recieved_command.command_chosen=exit_game;
        return recieved_command;
    }
    else//not a command!
    {
        recieved_command.command_chosen=invalid_type;
        return recieved_command;
    }


    recieved_command.param_amount=0;
    token=strtok(NULL," \t\r\n");

    while(token!=NULL)
    {
        recieved_command.params[recieved_command.param_amount]=token[0]-'0';
        recieved_command.param_amount++;
        param_amount--;
        token=strtok(NULL," \t\r\n");
    }
    if(param_amount>0)
    {
        recieved_command.command_chosen=invalid_type;
    }
    return recieved_command;
    

}


int main()
{
    command temp;
    temp=parse_command();
    printf("type:%d \n",temp.command_chosen);
    printf("param1:%d \n",temp.params[0] );
    printf("param2:%d \n",temp.params[1]);
    printf("param3:%d \n",temp.params[2]);


    return 0;
}