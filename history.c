#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void add_command(char * command , history_t *history)
{
    if(history==NULL)
    {
        history_init(history);
    }
    if(history->size>=history->capacity)
    {
        return;
    }
    history->histrory_commands[history->size++] =strdup(command);
}
void print_commands(history_t * history)
{
    for(int i =0 ; i < history->size ; i++)
    {
        printf("%s\n" , history->histrory_commands[i]);
    }
}
void history_init(history_t * history)
{
    history->size = 0;
    history->capacity = 100;
        return;
}