#include<stdlib.h>
#include<stdio.h>
struct history
{    
     char * histrory_commands[100];
     size_t size;
     size_t capacity;
    /* data */
}typedef history_t;
void add_command(char * command , history_t *history);
void print_commands(history_t * history);
void history_init(history_t * history);