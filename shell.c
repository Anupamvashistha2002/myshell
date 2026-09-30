#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include "parse.h"
#include<err.h>
#include<errno.h>
#include<fcntl.h>


int main(void)

{
    char command[1024];
    char *argv[MAX_ARGS];
    char buf[64];
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
        if (argc==0)
        {
            continue;
        }
        if(strcmp(argv[0],"exit")==0)
        {
            break;
        }
        
        //implement pwd
        if(strcmp(argv[0],"pwd")==0)
        {
            if(getcwd(buf,sizeof(buf))!=NULL)
            {
                printf("current working dir is: %s\n",buf);
                
            }
            else{
                perror("getcwd");
                
            }
            continue;
        }
        //cd command implementation
        if(strcmp(argv[0],"cd")==0)
        {
            if(argv[1]==NULL)
            {
              fprintf(stderr,"cd: missing args \n");
            }

            else if(chdir(argv[1])==-1)  //Location not found
            {
                perror("cd");
            }
            // else if(argv[1]==NULL) //No path provided to cd like : cd <nothing_here>
            // {
            //     perror("Please provide argument to cd: \n");
            // }
           
            continue;
        }
        int redirect=0;
        int redirect_append=0;
        char *output_file=NULL;
        int syntax_error=0;

        for(int i=0;i<argc;i++)
        {

            
            if(strcmp(argv[i],">")==0)
            {
                if(argv[i+1]==NULL)
                {
                    fprintf(stderr,"myshell: expected filename after >\n");
                    syntax_error=1;
                    break;
                }
                redirect_append=1;
                output_file=argv[i+1];
                argv[i]=NULL;
                break;
            }

            if(strcmp(argv[i],">>")==0)
            {
                if(argv[i+1]==NULL)
                {
                    fprintf(stderr,"myshell:expeected filename after >> \n");
                    syntax_error=1;
                    break;
                }
                redirect_append=1;
                output_file=argv[i+1];
                argv[i]=NULL;
                break;
            }
        }
        // printf("redirect=%d\n",redirect);
        // if(output_file!=NULL)
        // {
        //     printf("output_file=%s\n",output_file);
        // }
        if(syntax_error)
        {
            continue;
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
        // int fd=open(output_file,O_WRONLY|O_TRUNC|O_CREAT,0644);
        // if(fd==-1)
        // {
        //     perror("failed to open: \n");
        //     return 1;
        // }
        // dup2(fd,STDOUT_FILENO);
        // printf("check av \n");
        //IMPLEMENTED REDIRECTION(>)
        if(redirect==1)
        {
            int fd=open(output_file,O_WRONLY|O_TRUNC|O_CREAT,0644);
            if(fd==-1)
            {
                perror("Failed to open: \n");
                return 1;
            }
            int dval=dup2(fd,STDOUT_FILENO);
            if(dval==-1)
            {
                perror("fail \n");
                return 1;
            }
            close(fd);
        }
        if(redirect_append==1)
        {
             int fd=open(output_file,O_WRONLY|O_APPEND|O_CREAT,0644);
            if(fd==-1)
            {
                perror("Failed to open: \n");
                return 1;
            }
            int dval=dup2(fd,STDOUT_FILENO);
            if(dval==-1)
            {
                perror("fail \n");
                return 1;
            }
            close(fd);
        }

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