#include<stdlib.h>
#include<stdio.h>
#include<wait.h>
#include<string.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "history.h"
int main(int agrc , char*argv[]){
    char error_message[30] = "An error has occurred\n";
    
    if(agrc >1)
    {
        printf("%s" ,error_message);
        exit(0);
    }
   history_t history;
   history_init(&history);
    while(1)
    {
         printf("wish> ");
        //read teh line of the Command
        char* buffer = NULL;
        char * pip_char;
        char * second_process;
        char * redirection_character;
        size_t n=0;
        char arg2_read_commnad[100];
        char arg2_command_path[200]="/usr/bin/";
        char * argument_2 [5];
        int pipefd[2];
        getline(&buffer , &n ,stdin);
        if(buffer[0] =='\0') continue;
         buffer[strcspn(buffer, "\n")] = '\0';
         add_command(buffer,&history);
         if(strcmp(buffer , "history")==0)
         {
            print_commands(&history);
            continue;
         }
        char *buffer_copy = strdup(buffer);
        redirection_character = strchr(buffer_copy , '>');
        pip_char = strchr(buffer_copy , '|');
        if(pip_char!=NULL)
        {
            pip_char++;
            while(isspace((unsigned) *pip_char))
            {
                pip_char++;
            }
            char *read_command_temp = strdup(pip_char);
            sscanf(read_command_temp,"%s",arg2_read_commnad);
            int arg2_index= 0;
            char * p2_token = strtok(pip_char , " ");
            while(p2_token!=NULL)
            {
                argument_2[arg2_index++] = p2_token;
                p2_token = strtok(NULL , " ");
            }
            argument_2[arg2_index] = NULL;
            strcat(arg2_command_path , arg2_read_commnad);
            pipe(pipefd);
            int arg2_access_result = access(arg2_command_path,X_OK);
             if(arg2_access_result!=0)
            {
                printf("%s" , error_message);
                continue;
            }
        }
        //Parse the line
        char  read_command[100];
        sscanf(buffer, "%s",read_command);
        free(buffer);
        //execute command ;
        char command_arguments[100] = "/usr/bin/";
        strcat(command_arguments ,read_command);
        
       int arg1_access_result= access(command_arguments ,X_OK);
       
       if(arg1_access_result!=0)
       {
        printf("%s" , error_message);
        continue;
       }
       char * token = strtok(buffer_copy , " ");
        char *arguments[5];
        int i =0;  
        while(token!=NULL)
        {
            if(strcmp(token , ">")==0 || strcmp(token , "|")==0)
            break;
            
            arguments[i++] = token;
            token = strtok(NULL," ");
        }
        
        
       
        arguments[i] = NULL;     
       
       int child_pid= fork();
      
       if(child_pid==-1)
       {
            printf("%s" , error_message);
            exit(1);
       }
       else if(child_pid==0)
       {
         if(redirection_character!=NULL)
        {
            char *file_name = strtok(NULL , " ");
            FILE * file= fopen(file_name ,"w+");
            if(file==NULL)
            {
                printf("%s" ,error_message);
                continue;
            }
            dup2(file->_fileno , 1);
           fclose(file);
        }
        
        if(pip_char!=NULL)
        {
                close(pipefd[0]);
            dup2(pipefd[1],STDOUT_FILENO);
            close(pipefd[1]);
            second_process = strtok(NULL , " ");
        }
           
        execv(command_arguments,arguments);
        exit(1);
       }
       else{
        int second_child_pid;
       
        if(pip_char!=NULL)
       {
         close(pipefd[1]);
        second_child_pid =fork();
        if(second_child_pid==-1)
        {
            printf("%s" , error_message);
            exit(1);  
        }
        else if(second_child_pid==0)
        {
            close(pipefd[1]);
            dup2(pipefd[0] , STDIN_FILENO);
            close(pipefd[0]);
            execv(arg2_command_path ,argument_2);
            exit(1);
        }
        waitpid(second_child_pid , NULL , 0);
        close(pipefd[0]);
       }
       waitpid(child_pid, NULL , 0);
       
       }
        
    }
    return 0;
}