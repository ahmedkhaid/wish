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
    printf("wish> ");
    while(1)
    {
        //read teh line of the Command
        char* buffer = NULL;
        size_t n;
        getline(&buffer , &n ,stdin);
        //Parse the line
        char  read_command[100];
        sscanf(buffer, "%s",read_command);
        //execute command ;
        char command_arguments[100] = "/usr/bin/";
        strcat(command_arguments ,read_command);
       int access_result= access(command_arguments ,X_OK);
       if(access_result!=0)
       {
        printf("%s" , error_message);
       }
       int child_pid= fork();
       if(child_pid==-1)
       {
            printf("%s" , error_message);
            exit(1);
       }
       else if(child_pid==0)
       {
        char * args[]={command_arguments,NULL};
        execv(command_arguments,args);
       };

        exit(1);
    }
    return 0;
}