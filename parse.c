#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define MAX_ARGS 64
int parse(char *command,char* argv[])
{
    int i=0;
    char *p=command;
    while(*p != '\0' && i<MAX_ARGS-1)
    {
        while(*p == ' ' || *p=='\t' || *p='\n')
        {
            p++;
        }
        if(*p=='\0')
        {
            break;
        }
        argv[i]=p;
        i++;

        //move the p to end of current arg
        if(*p==' ' && *p=='\n' && *p=='\t' && *p=='\0')
        {
            p++;
        }
        //end of current arg
        if(*p!='\0')
        {
            *p='\0';
            p++;        
        }
        //NULL Terminate the array
        argv[i]=NULL;
        return i;
    }

}


int main()
{
    char *argv[MAX_ARGS];
    char command[1024];
    printf("Enter the command: ");
    if(fgets(command,sizeof(command),stdin)==NULL)

    {
        return 1;//if it fails

    }
    int argc=parse(command,argv);
    // command[strcspn(command,"\n")]='\0';
    

     
    // char *argv[10];
    // argv[0]=command;
    // char *p=command;
    // while(*p!='\0')
    // {
    //     if(*p==' ')
    //     {
    //         *p='\0';
    //         argv[1]=p+1;
    //         // if(*p==' ')
    //         // {
    //         //     argv[2]=p+1;
    //         // }
    //         char* k=argv[1];
    //         while(*k!='\0')
    //         {
    //             if(*k==' ')
    //             {
    //                 *k='\0';
    //                 argv[2]=k+1;
    //                 break;
    //             }
    //             k++;
    //         }
    //         break;
    //     }
    //     p++;
    // }
    // printf("argv[0] = %s\n",argv[0]);
    // printf("argv[1] = %s\n",argv[1]);
    // printf("argv[2]: %s\n",argv[2]);
    return 0;
}