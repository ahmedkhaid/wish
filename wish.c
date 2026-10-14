#include<stdlib.h>
#include<stdio.h>
#include<wait.h>
#include<string.h>
#include <unistd.h>

int main(int agrc , char*argv[]){
    char error_message[30] = "An error has occurred\n";
    
    if(agrc >1)
    {
        printf("%s" ,error_message);
        exit(0);
    }
   
    while(1)
    {
         printf("wish> ");
        //read teh line of the Command
        char* buffer = NULL;
        char * pip_char;
        char * redirection_character;
        size_t n;
        getline(&buffer , &n ,stdin);
        if(buffer[0] =='\0') continue;
         buffer[strcspn(buffer, "\n")] = '\0';
        char *buffer_copy = strdup(buffer);
        redirection_character = strchr(buffer_copy , '>');
        pip_char = strchr(buffer_copy , '|');
        char *second_command;
        //Parse the line
        char  read_command[100];
        char file_name[100];
        char command_options[100];
        sscanf(buffer, "%s",read_command);
        free(buffer);
        //execute command ;
        char command_arguments[100] = "/usr/bin/";
        strcat(command_arguments ,read_command);
        
       int access_result= access(command_arguments ,X_OK);
       if(access_result!=0)
       {
        printf("%s" , error_message);
        continue;
       }
       int child_pid= fork();
       if(child_pid==-1)
       {
            printf("%s" , error_message);
            exit(1);
       }
       else if(child_pid==0)
       {
        char * token = strtok(buffer_copy , " ");
        char *arguments[5];
        int i =0;  
        while(token!=NULL)
        {
            if(strcmp(token , ">")==0)
            break;
            arguments[i++] = token;
            token = strtok(NULL," ");
        }
        char *file_name = strtok(NULL , " ");
        arguments[i] = NULL;
        if(redirection_character!=NULL)
        {
            FILE * file= fopen(file_name ,"w+");
            if(file==NULL)
            {
                printf("%s" ,error_message);
                continue;
            }
            dup2(file->_fileno , 1);
           fclose(file);
        }
        else if(pip_char!=NULL)
        {
            exit(1);
        }
        
        execv(command_arguments,arguments);
        exit(1);
       }
       else{
       wait(NULL);
       }
        
    }
    return 0;
}