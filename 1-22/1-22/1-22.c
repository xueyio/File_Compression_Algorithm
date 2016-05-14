//
//  main.c
//  1-22
//
//  Created by Xueyong Qian on 27/03/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 1000
#define COL 10
#define TABSTOP 4

void copy(char to[], char from[])
{
    int i;
    
    i = 0;
    while((to[i] = from[i])!='\0')
        ++i;
}

int getl(char s[], int lim, FILE*ifp)
{
    int c, i, n;
    
    for(i = n = 0; (c = getc(ifp))!=EOF && c!='\n'; ++n)
    {
        if(i<lim-2){
            s[i++] = c;
        }
    }
    if(c == '\n')
    {
        s[i++] = c;
        ++n;
    }
    s[i] = '\0';
    return n;
}

void detab(char *s)
{
    int count;
    char *temp = (char*)malloc(sizeof(char)*MAXLINE);
    count = 0;
    while(*s)
    {
        ++count;
        if(*s == '\t')
        {
            while(count%TABSTOP)
            {
                *temp++ = ' ';
                ++count;
            }
        }
        else
            *temp++ = *s;
        ++s;
    }
    *temp = '\0';
    copy(s,temp);
}

char *next_space(char *s)
{
    while (!isspace(*s)) {
        ++s;
    }
    while(isspace(*s))
    {
        ++s;
    }
    --s;
    return s;
}

char *next_col(char *s)
{
    int i;
    
    for(i = 0; *s != '\n'&& i < COL * TABSTOP; ++i)
    {
        ++s;
    }
    
    return s;
}
void fold(char *s)
{
    char *pos = s;
    char *temp;
    detab(s);
    while (*(pos = next_col(pos)) != '\n')
    {
        if(isspace(*(pos - 1)))
        {
            *(pos - 1) = '\n';
        }
        else
        {
            temp = next_space(pos);
            *temp  = '\n';
        }
    }
    
}

int main(int argc, const char * argv[])
{

    char line[MAXLINE];
    FILE *ifp = fopen("fold", "r");
    
    while(getl(line, MAXLINE, ifp))
    {
        fold(line);
        printf("%s",line);
    }
    fclose(ifp);
    return 0;
}

