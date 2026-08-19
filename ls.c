#include<stdint.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(void)
{
    pid_t pid=fork();
    if(pid==0)//child
    {
        printf("Entered child\n");
        printf("About to do ls \n");
        execlp("ls","ls",NULL);
        perror("Failed");

    }
    else //parent
    {
        printf("Parent process \n");
        waitpid(pid,NULL,0);
        printf("Finished \n");

    }
    return 0;

}