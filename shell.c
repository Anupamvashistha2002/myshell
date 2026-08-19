#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
int main(void)

{
    char command[1024];

    while(1)
    {
        printf("myshell> ");
        fflush(stdout);
        fgets(command,sizeof(command),stdin);
        command[strcspn(command,"\n")]='\0';
        pid_t pid=fork();
        if(pid==0)//child
        {
            printf("About to do ls \n");
            execlp(command,command,NULL);
            perror("Failed");
            return 1;
        }
        else{
            printf("we are in parent");
            waitpid(pid,NULL,0);
        }


    }
    return 0;
}