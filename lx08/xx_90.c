//练习指向指针的指针变量

#include<stdio.h>

int main(){
    char *name[] = {"Follow me","BASIC","Great Wall","FORTRAN","Computer design"};
    char **p;
    int n=5;
    for (int  i = 0; i < 5; i++)
    {
        p = name+i;
        printf("%s\n",*p);
    }   
}