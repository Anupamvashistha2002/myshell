#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include "parse.h"

int parse(char *command,char* argv[])
{
    int i=0;
    char *p=command;
    while(*p != '\0' && i<MAX_ARGS-1)
    {
        while(*p == ' ' || *p=='\t' || *p=='\n')
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
        while(*p!=' ' && *p!='\n' && *p!='\t' && *p!='\0')
        {
            p++;
        }
        //end of current arg
        if(*p!='\0')
        {
            *p='\0';
            p++;        
        }
       
       
      
    }
    //NULL terminate the array
     argv[i]=NULL;
      return i;

}
