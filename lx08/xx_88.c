//练习返回指针值的函数

#include<stdio.h>
float *search(float (*p)[4]);
int main(){
    float score[][4] = {{65,78,65,84},{78,50,85,54},{65,78,89,52}};
    int i,j;
    float *p;
     printf("\n");
    for ( i = 0; i < 3; i++)
    {
        p = search(score+i);
        if (p == *(score+i))
        {
            printf("NO.%d score: ",i);
            for ( j = 0; j < 4; j++)
            {
                printf("%5.2f ",*(p+j));
            }
            printf("\n\n");
        }  
    }
    return 0;
}

float *search(float (*p)[4]){
    float *result;
    result = NULL;
    int i;
    for ( i = 0; i < 4; i++)
    {
        if (*(*p+i)<60)
        {
            result = *p;
        }    
    }
    return(result);
}