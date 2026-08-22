#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include "parse.h"
#include<err.h>
#include<errno.h>


int main(void)

{
    char command[1024];
    char *argv[MAX_ARGS];

    while(1)
    {
        printf("myshell> ");
        fflush(stdout);
        if(fgets(command,sizeof(command),stdin)==NULL)
        {
            perror("FAILED:");
            return 1;
        }
        command[strcspn(command,"\n")]='\0';
        int argc=parse(command,argv);

        //cd command implementation
        if(strcmp(argv[0],"cd")==0)
        {

            if(chdir(argv[1])==-1)  //Location not found
            {
                perror("cd");
            }
            else if(argv[1]==NULL) //No path provided to cd like : cd <nothing_here>
            {
                perror("Please provide argument to cd: \n");
            }
            else{
            printf("Working Directory changed\n");
            }
            continue;
        }

        if(argc==0)
        {
            fprintf(stderr,"Failed:Please enter arguments");
            return 1;
        }

        pid_t pid=fork();
        if(pid<0)
        {

            printf("Failed to fork \n");
            return 1;
        }
        else if(pid==0)//child
        {
            // printf("About to do ls \n");
            // execlp(command,command,NULL);
            // perror("Failed");
            // return 1;
        //EXECVP implementation
        if(execvp(argv[0],argv)==-1)

        {
            perror("Failed \n");
            return 1;
        }
        }
        else{
            
            waitpid(pid,NULL,0);
        }


    }
    return 0;
}