#include<stdio.h>
#include<string.h>
#include<unistd.h>



int main()
{
    char command[1024];
    printf("Enter the command: ");
    fgets(command,sizeof(command),stdin);
    command[strcspn(command,"\n")]='\0';
    char *argv[10];
    argv[0]=command;
    char *p=command;
    while(*p!='\0')
    {
        if(*p==' ')
        {
            *p='\0';
            argv[1]=p+1;
            break;
        }
        p++;
    }
    printf("argv[0] = %s\n",argv[0]);
    printf("argv[1] = %s\n",argv[1]);
    return 0;
}