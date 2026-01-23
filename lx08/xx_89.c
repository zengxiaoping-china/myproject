//练习指针数组

#include<stdio.h>
#include<string.h>

void sort(char *p[],int n){
    int i,j,k;
    char *temp;
    for ( i = 0; i < n-1; i++)
    {
        k=i;
        for ( j = i+1; j < n; j++)
        {
            if(strcmp(p[k],p[j])>0) k=j;
        }
        if(k != i)
        {
            temp = p[k],p[k] = p[i],p[i]=temp;
        }
        
    }
    
}

void print(char *p[],int n){
    for ( int i = 0; i < n; i++)
    {
        printf("%s\n",p[i]);
    }
}

int main(){
    char *name[]={"Follow me","BASIC","Great Wall","FORTRAN","Computer design"};
    int n=5;
    sort(name,n);
    print(name,n);
    return 0;
}